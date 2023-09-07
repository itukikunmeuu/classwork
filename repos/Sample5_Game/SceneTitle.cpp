#include "SceneTitle.h"
#include "DxLib.h"

//�萔��`
namespace
{
	//�t�F�[�h�̑��x
	constexpr int kFadeSpeed = 4;

	//�t�F�[�h�C����̑҂�����
	constexpr int kWaitFrame = 60;
}

SceneTitle::SceneTitle() :
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

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	//�t�F�[�h�̏�����
	m_fadeCount = 255; //���S�Ƀt�F�[�h�A�E�g����������Ԃ���
	m_fadeSpeed = -4;  //�t�F�[�h�C��������	-4:�t�F�[�h�C�� +4:�t�F�[�h�A�E�g�@0:�҂�����
	m_waitFrame = 0;

	//�O���t�B�b�N�̃��[�h
	m_bgHandle[0] = LoadGraph("data/TitleBg000.jpg");
	m_bgHandle[1] = LoadGraph("data/TitleBg001.jpg");
	m_bgHandle[2] = LoadGraph("data/TitleBg002.jpg");
	m_bgHandle[3] = LoadGraph("data/TitleBg003.jpg");
	//�ŏ��ɕ\������摜���w�肷��
	m_bgNo = 0;
}

void SceneTitle::Update()
{
	if (m_fadeSpeed == 0)
	{
		//�҂�����
		m_waitFrame++;
		if (m_waitFrame >= 60)
		{
			//�t�F�[�h�A�E�g�ɑJ��
			m_fadeSpeed = 4;
		}
	}
	else if (m_fadeSpeed < 0)
	{
		//�t�F�[�h�C����
		m_fadeCount += m_fadeSpeed;
		if (m_fadeCount <= kFadeSpeed)
		{
			m_fadeCount = 0;
			//�҂��ɑJ��
			m_fadeSpeed = 0;
			m_waitFrame = 0; //�҂����ԏ�����
		}
	}
	else //m_faedaSpeed > 0
	{
		//�t�F�[�h�A�E�g��
		m_fadeCount += m_fadeSpeed;
		if (m_fadeCount >= kWaitFrame)
		{
			//�摜��؂�ւ��ăt�F�[�h�C���ɑJ�ڂ���
			m_fadeSpeed = -4;

			//�\������摜��ύX
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
	//�w�肳��Ă���摜��\������
	DrawGraph(0, 0, m_bgHandle[m_bgNo], false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA,m_fadeCount);  //�����ȍ~�A�w�肵�������x�ŕ`�ʂ���
	DrawBox(0, 0, 640, 480,GetColor(0,0,0),true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  //���̐ݒ�i�ʏ�̕s�����`�ʁj�ɖ߂�
}

void SceneTitle::End()
{
	for (int i = 0; i < kBgNum; i++)
	{
	DeleteGraph(m_bgHandle[i]);
	}
}
