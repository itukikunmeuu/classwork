#include "SceneResult.h"
#include "DxLib.h"
#include <cassert>
#include "Game.h"

SceneResult::SceneResult() :
	m_gameoverHandle(-1),
	m_isSceneEnd(false)
{
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	m_gameoverHandle = LoadGraph("data/gameover.jpg");
	assert(m_gameoverHandle != -1);
}

void SceneResult::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_2) //パッドの1ボタン　or　キーボードのｚキー
	{
		//タイトル画面を終了しSceneMainに移動する処理を書きたい！
		m_isSceneEnd = true;
	}
}

void SceneResult::Draw()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_gameoverHandle, &width, &height);

	DrawGraph(Game::kScreenWidth /2 - width / 2, 
		Game ::kScreenHeight / 2 - height / 2,
		m_gameoverHandle, false);
}

void SceneResult::End()
{
	DeleteGraph(m_gameoverHandle);
}
