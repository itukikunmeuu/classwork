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
	//BGM�̓ǂݍ���
	m_bgmHandle = LoadSoundMem("data/sound/Titlemp3");

	//���ʉ��̓ǂݍ���
	m_decideSe = LoadSoundMem("data/sound/Se.mp3");

	m_isSceneEnd = false;

	//BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	//�t�F�[�h�C�������邽�߉���0����n�߂�
	int volume = 255 - m_fadeAlpha;
	ChangeVolumeSoundMem(volume, m_bgmHandle);
}

void SceneTitle::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_1) //�p�b�h��1�{�^���@or�@�L�[�{�[�h�̂��L�[
	{
		//�^�C�g����ʂ��I����SceneMain�Ɉړ����鏈�������������I
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
	//��ʂ̃t�F�[�h�n�𗘗p���ăT�E���h�̉��ʂ����肷��

}

void SceneTitle::Draw()
{
	DrawString(120, 120, "�^�C�g�����", GetColor(255, 255, 255));
	DrawString(120, 120+16, "1�{�^���������Ă�������", GetColor(255, 255, 255));

}

void SceneTitle::End()
{
	//BGM���~�߂�
	StopSoundMem(m_bgmHandle);

	//BGM������������폜
	DeleteSoundMem(m_bgmHandle);
	//���ʉ�������������폜
	DeleteSoundMem(m_decideSe);
}

bool SceneTitle::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
