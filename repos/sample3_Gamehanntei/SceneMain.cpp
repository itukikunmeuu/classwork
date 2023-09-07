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
	m_player.SetFill(true);				//�v���C���[�̋�`�͓h��Ԃ�
	m_player.SetMouseTrase(true);			//�v���C���[�̋�`�̓}�E�X�ɒǏ]
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
		m_rect[i].Draw();  //rect�̖��t���[���̍X�V����
		//�ړ���̏������ē����蔻����Ƃ�
	//IsCollision()
	//	if (IsCollision(player, rect[i]))
		if (m_player.IsCollision(m_rect[i]))
		{
			//�������Ă���ꍇ�̏���
			m_rect[i].SetColor(GetColor(255, 0, 0)); //�Ԃ�����
		}
		else
		{
			//�������Ă��Ȃ��ꍇ�̏���
			m_rect[i].SetColor(GetColor(255, 255, 255)); //��������
		}
	}
}

void SceneMain::Draw()
{
}

void SceneMain::End()
{
}
