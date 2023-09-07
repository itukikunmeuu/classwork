#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"

SceneTitle::SceneTitle() :
	m_isSceneEnd(false),
	m_decideSe(-1),
	m_bgmHandle(-1),
	m_fadeAlpha(255)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	//BGMの読み込み
	m_bgmHandle = LoadSoundMem("data/sound/Titlemp3");

	//効果音の読み込み
	m_decideSe = LoadSoundMem("data/sound/Se.mp3");

	m_isSceneEnd = false;

	//BGMの再生
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	//フェードインさせるため音量0から始める
	int volume = 255 - m_fadeAlpha;
	ChangeVolumeSoundMem(volume, m_bgmHandle);
}

void SceneTitle::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_1) //パッドの1ボタン　or　キーボードのｚキー
	{
		//タイトル画面を終了しSceneMainに移動する処理を書きたい！
		m_isSceneEnd = true;
	}

	if (m_isSceneEnd)
	{
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
	//画面のフェード地を利用してサウンドの音量を決定する

}

void SceneTitle::Draw()
{
	DrawString(120, 120, "タイトル画面", GetColor(255, 255, 255));
	DrawString(120, 120+16, "1ボタンを押してください", GetColor(255, 255, 255));

}

void SceneTitle::End()
{
	//BGMを止める
	StopSoundMem(m_bgmHandle);

	//BGMをメモリから削除
	DeleteSoundMem(m_bgmHandle);
	//効果音をメモリから削除
	DeleteSoundMem(m_decideSe);
}

bool SceneTitle::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
