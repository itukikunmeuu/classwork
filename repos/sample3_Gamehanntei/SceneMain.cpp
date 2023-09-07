#include "SceneMain.h"
#include "DxLib.h"

SceneMain::SceneMain()
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_player.Init();
	m_player.SetFill(true);				//プレイヤーの矩形は塗りつぶす
	m_player.SetMouseTrase(true);			//プレイヤーの矩形はマウスに追従
	for (int i = 0; i < kRectNum; i++)
	{
		m_rect[i].Init();
		m_rect[i].SetRandom();
	}
}

void SceneMain::Update()
{
	m_player.Update();
	for (int i = 0; i < kRectNum; i++)
	{
		m_rect[i].Update();
	}
	m_player.Draw();
	for (int i = 0; i < kRectNum; i++)
	{
		m_rect[i].Draw();  //rectの毎フレームの更新処理
		//移動後の情報を見て当たり判定をとる
	//IsCollision()
	//	if (IsCollision(player, rect[i]))
		if (m_player.IsCollision(m_rect[i]))
		{
			//当たっている場合の処理
			m_rect[i].SetColor(GetColor(255, 0, 0)); //赤くする
		}
		else
		{
			//当たっていない場合の処理
			m_rect[i].SetColor(GetColor(255, 255, 255)); //白くする
		}
	}
}

void SceneMain::Draw()
{
}

void SceneMain::End()
{
}
