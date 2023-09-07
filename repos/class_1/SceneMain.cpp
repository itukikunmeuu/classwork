#include "SceneMain.h"
#include "DxLib.h"
//�w�b�_�[�ł̓N���X�̃v���g�^�C�v�錾�̂�
//�\�[�X�t�@�C�����ŃC���N���[�h���s��
#include "Player.h"

SceneMain::SceneMain() :
	m_frameCount(0) //�R���X�g���N�^�������q���g�p���ď���������
{
	//�����܂ł̓����o�[�̃������m�ۂ̓R���X�g���N�^��
	m_pPlayer = new Player;
}

SceneMain::~SceneMain()
{
	//�����܂ł̓����o�[�̊J���̓f�X�g���N�^��
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

//���t���[���s��������Update�ɋL�q����
void SceneMain::Update()
{
	m_frameCount++;
}

//Update�ŏ����������ʂ𔽉f�������\����Draw�ōs��
void SceneMain::Draw() const
{
	DrawFormatString(8, 8, GetColor(255, 255, 255), "%d", m_frameCount);
		for (int i = 0; i < kPlayerNum; i++)
		{
		m_player[i].Draw();
		}
}
