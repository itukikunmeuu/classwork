#include "SceneMain.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace
{
	//ゲームオーバー時に表示する文字列
	const char* const kGameOverString = "ゲームオーバー";

	//敵の初期生成感覚(フレーム数)
	constexpr int kEnemyWaitDefault = 60;
	//敵の最短生成感覚
	constexpr int kEnemyWaitFrameMin = 3;
	//敵のせいせかんかっくを的なん隊生成するたびに短くするか
	constexpr int kEnemyWaitFrameChangeNum = 5;
	//一度生成感覚を短くするときに何フレーム短くするか
	constexpr int kEnemyWaitFrameChangeFrame = 2;
	
}

SceneMain::SceneMain() :
	m_playerHandle(-1),
	m_enemyHandle(-1),
	m_player(), //クラスを初期化するとき、()の中にはコンストラクタの引数を入れる
	//playerクラスに関してはコンストラクタに引数がないので()でOK
	m_enemy(),
	m_isGaneOver(false),
	m_isSceneEnd(false),
	m_playFrameCount(0),
	m_enemyCreateNum(0),
	m_enrmyWaitFrame(0),
	m_bgmHandle(-1),
	m_fadeAlpha(255)  //不透明で初期化
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	ChangeFont("HGP行書体");
	SetFontSize(48);

	//グラフィックのロード
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);  //グラフィックのロードに失敗していいたら止める
	m_enemyHandle = LoadGraph("data/image/enemy.png");
	assert(m_enemyHandle != -1);  //グラフィックのロードに失敗していいたら止める

	//サウンドのロード
	m_bgmHamdle = LoadSoundMem("data/image/Main.mp3");
	m_enemyStaetSe = LoadSoundMem("data/image/enemy.mp3");
	//BGMの再生
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	//フェードインさせるため音量0から始める
	ChangeVolumeSoundMem(0, m_bgmHandle);

	//プレイヤーの初期化
	m_player.Init();
	m_player.SetGraphHandle(m_playerHandle);
	//敵の初期化
	for (int i = 0; i < kEnemyMax; i++)
	{
	m_enemy[i].Init();
	m_enemy[i].SetGraphHandle(m_enemyHandle);
	m_enemy[i].SetStartPos(); //グラフィックを設定した後初期値に設定
	}

	m_isGaneOver = false;
	m_isSceneEnd = false;
	m_playFrameCount = 0;
	m_enemyCreateNum = 0;

	m_fadeAlpha = 255;
}

void SceneMain::Update()
{
	//ゲームオーバーになったら各処理を行わず、即Update()を終了させる
	if (m_isGaneOver) 
	{
		if (m_isSceneEnd)
		{
			//フェードアウト
			m_fadeAlpha += 8;
				if (m_fadeAlpha > 255)
				{
					m_fadeAlpha = 255;
				}
		}
		//1ボタンorZキーが押されたらゲームオーバー画面へ
		int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (pad & PAD_INPUT_1)  //1ボタンが押された
		{
			m_isSceneEnd = true;
		}
		return;
	
	}
	//フェードイン
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	//生き残り時間（フレーム数）を増やす
	m_playFrameCount++;

	m_player.Update();
	for (int i = 0; i < kEnemyMax; i++)
	{
		m_enemy[i].Update();
		if (IsCollision(m_player, m_enemy[i]))
		{
			m_isGaneOver = true;
		}

	}
	//一定間隔で敵を生成
	m_enrmyWaitFrame++;
	//敵5体生成するたびに敵の生成感覚が1フレーム短くなる
	int waitFrame = kEnemyWaitDefault;
	waitFrame -= (m_enemyCreateNum / 5) * 1;
	//一番短くて3フレーム感覚
	if (waitFrame < 3) waitFrame = 3;

	if (m_enrmyWaitFrame >= waitFrame)
	{
		//現在使われていない敵キャラクターを探して
		//そいつをStaetさせる
		for (int i = 0; i < kEnemyMax; i++)
		{
			//m_enemy[i].isExist()がfalseの場合存在していない
			//のでそいつを使う
			if (!m_enemy[i].isExist())
			{
				m_enrmyWaitFrame = 0;
				m_enemyCreateNum++;
				m_enemy[i].Start();

				//効果音を流す
				PlaySoundMem(m_enemyStaetSe, DX_PLAYTYPE_BACK);
				break; //1体制性したら終了
			}
		}
	}
}

void SceneMain::Draw()
{
	m_player.Draw();
	for (int i = 0; i < kEnemyMax; i++)
	{
	m_enemy[i].Draw();
	}

	//生存時間を表示
	//分:秒.ミリ秒
//	int sec = m_playFrameCount / 60;
	int milliSec = m_playFrameCount * 1000 / 60;
	int sec = (milliSec / 1000) % 60;
	int min = (milliSec / 1000) / 60;
	milliSec %= 1000; //ミリ秒の部分のみ残す
	//文字列の横幅取得
	int strWidth = GetDrawFormatStringWidth("%3d:%02d:%03d", min, sec, milliSec);

	DrawFormatString(Game::kScreenWidth/2, 8, GetColor(255, 255, 255),
		"%3d:%02d:%03d", min, sec, milliSec);

	for (int i = 0; i < kEnemyMax; i++)
	{
		if (IsCollision(m_player, m_enemy[i]))
		{
			//画面中央にゲームオーバー表示

			//表示する文字の横幅を取得する
			//GetDrawStringWidth(char * strung, int strLen);
			int len = strlen(kGameOverString);
			int width = GetDrawStringWidth("ゲームオーバー", len);
			int height = GetFontSize();
			//当たっているかどうかを確認するデバッグ表示
			DrawString(Game::kScreenWidth / 2 - width / 2,
				Game::kScreenHeight / 2 - height / 2,
				"ゲームオーバー", GetColor(255, 32, 32));
		}
	}
	//フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha); //半透明で表示開始
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255),true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

bool SceneMain::IsCollision(const Player& player, const Enemy& enemy)
{
	//存在しない敵とは当たらない
	if (!enemy.isExist()) return false;

	//当たり判定

	//プレイヤーよりも完全に左にいる場合は当たっていない
	//プレイヤー左端よりも左に敵の右側がある場合は当たっていない
	if (player.getLeft() > enemy.getRight())
	{
		//完全に左にいるので当たっていないことを確定
		return false; //確実に当たっていないのでfalse返す
	}
	//プレイヤーよりも完全にしたにいる場合は当たっていない
	//プレイヤー下端よりも完全に敵の上橋がある場合は当たっていない
	if (player.getBotton() < enemy.getTop())
	{
		//完全に左にいるので当たっていないことを確定
		return false;//確実に当たっていないのでfalse返す
	}
	//同様に完全に右にいるパターンを取り除く
	if (player.getRight() < enemy.getLeft())
	{
		//完全に左にいるので当たっていないことを確定
		return false;//確実に当たっていないのでfalse返す
	}

	//同様に完全に上にいるパターンを取り除く
	if (player.getTop() > enemy.getBotton())
	{
		//完全に左にいるので当たっていないことを確定
		return false;//確実に当たっていないのでfalse返す
	}
	return true;
}


void SceneMain::End()
{
	//メモリからグラフィックの削除する
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_playerHandle);
	//メモリからサウンドを削除
	DeleteSoundMem(m_enemyStaetSe);
}