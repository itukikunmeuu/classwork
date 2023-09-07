#include "Enemy.h"
#include<cassert>
#include "DxLib.h"

namespace
{
	//�ړ����x
	constexpr int kMoveSpeed = 4;

}

//�R���X�g���N�^
Enemy::Enemy() :
	m_handle(-1),
	m_kGraphWidth(0),
    m_kGraphHeight(0),
	m_posX(GetRand(640 - m_kGraphWidth)),
	m_posY(GetRand(480 - m_kGraphHeight)),
	m_moveX(kMoveSpeed)
{
	if (GetRand(1))
	{
		m_moveX *= -1;
	}
}

//�f�X�g���N�^
Enemy::~Enemy()
{
	DeleteGraph(m_handle);
}
	
void Enemy::Init()
{

}
	
void Enemy::Update()
{
	m_posX += m_moveX;
	if (m_posX < 0)
	{
		m_posX = 0;
		m_moveX *= -1;
	}
	if (m_posX > 640 - m_kGraphWidth)
	{
		m_posX = 640 - m_kGraphWidth;
		m_moveX *= -1;
	}
}
void Enemy::Draw() const
{
	int posX = m_posX;
	int posY = m_posY;

	posX += GetRand(5) - 2;
	posY += GetRand(5) - 2;

	DrawGraph(posX, posY, m_handle, false);
}

void Enemy::SetHandle(int handle)
{
	m_handle = handle;
	//�g�p����O���t�B�b�N�̃T�C�Y���擾����
	GetGraphSize(m_handle,&m_kGraphWidth,&m_kGraphHeight);
	
}
void Enemy::SetStaetPos()
{
	//�O���t�B�b�N�̃T�C�Y�����肵�Ă��Ȃ���
	//��ʔ����ɕ\������邩��

	//�O���t�B�b�N�����肷��O�ɌĂ΂�Ă����炻��ɋC�Â��悤�ɂ�����
	//�O���t�B�b�N�����܂�O�ɂ����ɗ�����~�܂�悤�ɂ�����
	//assert(�~�܂�Ȃ�����)
	assert(m_hamdle != -1);
	m_posX = GetRand(640 - m_kGraphWidth);
	m_posY = GetRand(640 - m_kGraphHeight);
}