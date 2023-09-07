#include "SceneMain.h"
#include "DxLib.h"
//ヘッダーではクラスのプロトタイプ宣言のみ
//ソースファイル内でインクルードを行う
#include "Player.h"

SceneMain::SceneMain() :
	m_frameCount(0) //コンストラクタ初期化子を使用して初期化する
{
	//慣れるまではメンバーのメモリ確保はコンストラクタで
	m_pPlayer = new Player;
}

SceneMain::~SceneMain()
{
	//慣れるまではメンバーの開放はデストラクタで
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void SceneMain::Init()
{
	for (int i = 0; i < kPlayerNum; i++)
	{
	m_player[i].Init();
	}
}

//毎フレーム行う処理をUpdateに記述する
void SceneMain::Update()
{
	m_frameCount++;
}

//Updateで処理した結果を反映させた表示をDrawで行う
void SceneMain::Draw() const
{
	DrawFormatString(8, 8, GetColor(255, 255, 255), "%d", m_frameCount);
		for (int i = 0; i < kPlayerNum; i++)
		{
		m_player[i].Draw();
		}
}
