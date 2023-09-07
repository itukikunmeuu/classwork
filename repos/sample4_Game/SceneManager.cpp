#include "SceneManager.h"
#include "DxLib.h"

namespace
{
	//フェードの速度
	constexpr int kFadeSpeed = 4;

	//フェードイン後の待ち時間
	constexpr int kWaitFrame = 60;
}

SceneManager::SceneManager() :
	m_runScene(kSceneKindTitle),
	m_title(),   //クラスの初期化時は()の中にコンストラクタの引数を書く
	m_main(),    //今回はどのシーンもコンストラクタで引数しないので
	m_result(),   //m_title()のような書き方でOK
	m_bgNo(0),
	m_fadeCount(0),
	m_fadeSpeed(0),
	m_waitFrame(0)
{
	for (int i = 0; i < kBgNum; i++)
	{
		m_bgHandle[i] = -1;
	}
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
		//フェードの初期化
		m_fadeCount = 255; //完全にフェードアウトしきった状態から
		m_fadeSpeed = -4;  //フェードインさせる	-4:フェードイン +4:フェードアウト　0:待ち時間
		m_waitFrame = 0;
	//初期化処理
	//実行したいシーンの初期化を行う
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.Init();
		m_handle[0] = LoadGraph("data/haikei2.png");

		break;
	case kSceneKindMain:
		m_main.Init();
		m_handle[0] = LoadGraph("data/haikei1.png");
		break;
	case kSceneKindResult:
		m_result.Init();
		break;
	default:
		break;
	}

}

void SceneManager::Update()
{
	//前にフレームの時点で書士が終わっていたらシーンのきり替え
	//シーンの切り替えを行う
	switch (m_runScene)
	{
	case kSceneKindTitle:
		//タイトル画面の終了をチェック
		if (m_title.IsSceneEnd())
		{
			m_title.End();

			//ゲームシーンへ遷移
			m_runScene = kSceneKindMain; //次のフレーム以降、実行したいシーン
			m_main.Init(); //変更先シーンの初期化
		}
		break;
	case kSceneKindMain:
		//終了していたらSceneResultにきりかえる
		if (m_main.IsSceneEnd())
		{
			m_main.End(); //実行していたシーンの終了

			m_runScene =kSceneKindResult; //次のフレーム以降、実行したいシーン
			m_result.Init(); //変更先のシーンの初期化
		}
		break;
	case kSceneKindResult:
		//タイトルに戻る
		if (m_result.IsSceneEnd())
		{
			//シーンを切り替える
			m_result.End(); //実行していたシーンの終了処理

			m_runScene = kSceneKindTitle; //次のフレーム以降、実行したい
			m_title.Init(); //変更先のシーンの初期化z
		}
		break;
	default:
		break;
	}

	//各シーンの更新を行う
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.Update();
		break;
	case kSceneKindMain:
		m_main.Update();
		break;
	case kSceneKindResult:
		m_result.Update();
		break;
	default:
		break;
	}
}

void SceneManager::Draw()
{
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.Draw();
		break;
	case kSceneKindMain:
		m_main.Draw();
		break;
	case kSceneKindResult:
		m_result.Draw();
		break;
	default:
		break;
	}
}

void SceneManager::End()
{
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_title.End();
		break;
	case kSceneKindMain:
		m_main.End();
		break;
	case kSceneKindResult:
		m_result.End();
		break;
	default:
		break;
	}
}






void SceneTitle::Init()
{
	//フェードの初期化
	m_fadeCount = 255; //完全にフェードアウトしきった状態から
	m_fadeSpeed = -4;  //フェードインさせる	-4:フェードイン +4:フェードアウト　0:待ち時間
	m_waitFrame = 0;

	//グラフィックのロード
	m_bgHandle[0] = LoadGraph("data/TitleBg000.jpg");
	m_bgHandle[1] = LoadGraph("data/TitleBg001.jpg");
	m_bgHandle[2] = LoadGraph("data/TitleBg002.jpg");
	m_bgHandle[3] = LoadGraph("data/TitleBg003.jpg");
	//最初に表示する画像を指定する
	m_bgNo = 0;
}

void SceneTitle::Update()
{
	if (m_fadeSpeed == 0)
	{
		//待ち時間
		m_waitFrame++;
		if (m_waitFrame >= 60)
		{
			//フェードアウトに遷移
			m_fadeSpeed = 4;
		}
	}
	else if (m_fadeSpeed < 0)
	{
		//フェードイン中
		m_fadeCount += m_fadeSpeed;
		if (m_fadeCount <= kFadeSpeed)
		{
			m_fadeCount = 0;
			//待ちに遷移
			m_fadeSpeed = 0;
			m_waitFrame = 0; //待ち時間初期化
		}
	}
	else //m_faedaSpeed > 0
	{
		//フェードアウト中
		m_fadeCount += m_fadeSpeed;
		if (m_fadeCount >= kWaitFrame)
		{
			//画像を切り替えてフェードインに遷移する
			m_fadeSpeed = -4;

			//表示する画像を変更
			m_bgNo++;
			if (m_bgNo >= kBgNum)
			{
				m_bgNo = 0;
			}
		}
	}
}

void SceneTitle::Draw()
{
	//指定されている画像を表示する
	DrawGraph(0, 0, m_bgHandle[m_bgNo], false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);  //ここ以降、指定した透明度で描写する
	DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  //元の設定（通常の不透明描写）に戻す
}

void SceneTitle::End()
{
	for (int i = 0; i < kBgNum; i++)
	{
		DeleteGraph(m_bgHandle[i]);
	}
}
