#include "SceneManager.h"
#include "DxLib.h"

namespace
{
	//�t�F�[�h�̑��x
	constexpr int kFadeSpeed = 4;

	//�t�F�[�h�C����̑҂�����
	constexpr int kWaitFrame = 60;
}

SceneManager::SceneManager() :
	m_runScene(kSceneKindTitle),
	m_title(),   //�N���X�̏���������()�̒��ɃR���X�g���N�^�̈���������
	m_main(),    //����͂ǂ̃V�[�����R���X�g���N�^�ň������Ȃ��̂�
	m_result(),   //m_title()�̂悤�ȏ�������OK
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
		//�t�F�[�h�̏�����
		m_fadeCount = 255; //���S�Ƀt�F�[�h�A�E�g����������Ԃ���
		m_fadeSpeed = -4;  //�t�F�[�h�C��������	-4:�t�F�[�h�C�� +4:�t�F�[�h�A�E�g�@0:�҂�����
		m_waitFrame = 0;
	//����������
	//���s�������V�[���̏��������s��
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
	//�O�Ƀt���[���̎��_�ŏ��m���I����Ă�����V�[���̂���ւ�
	//�V�[���̐؂�ւ����s��
	switch (m_runScene)
	{
	case kSceneKindTitle:
		//�^�C�g����ʂ̏I�����`�F�b�N
		if (m_title.IsSceneEnd())
		{
			m_title.End();

			//�Q�[���V�[���֑J��
			m_runScene = kSceneKindMain; //���̃t���[���ȍ~�A���s�������V�[��
			m_main.Init(); //�ύX��V�[���̏�����
		}
		break;
	case kSceneKindMain:
		//�I�����Ă�����SceneResult�ɂ��肩����
		if (m_main.IsSceneEnd())
		{
			m_main.End(); //���s���Ă����V�[���̏I��

			m_runScene =kSceneKindResult; //���̃t���[���ȍ~�A���s�������V�[��
			m_result.Init(); //�ύX��̃V�[���̏�����
		}
		break;
	case kSceneKindResult:
		//�^�C�g���ɖ߂�
		if (m_result.IsSceneEnd())
		{
			//�V�[����؂�ւ���
			m_result.End(); //���s���Ă����V�[���̏I������

			m_runScene = kSceneKindTitle; //���̃t���[���ȍ~�A���s������
			m_title.Init(); //�ύX��̃V�[���̏�����z
		}
		break;
	default:
		break;
	}

	//�e�V�[���̍X�V���s��
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

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);  //�����ȍ~�A�w�肵�������x�ŕ`�ʂ���
	DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  //���̐ݒ�i�ʏ�̕s�����`�ʁj�ɖ߂�
}

void SceneTitle::End()
{
	for (int i = 0; i < kBgNum; i++)
	{
		DeleteGraph(m_bgHandle[i]);
	}
}
