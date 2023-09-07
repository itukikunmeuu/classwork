#include "Enemy.h"
#include "DxLib.h"
#include <cassert>
#include "Game.h"

namespace
{
    constexpr float kSpeed = 8.0f;
}

Enemy::Enemy() :
    m_handle(-1),
    m_width(0),
    m_height(0),
    m_isExist(),
//    m_posX(0.0f),
//    m_posY(0.0f),
    m_moveY(0.0f)
{
    for (int i = 0; i < kPosLogFrame; i++)
    {
        m_posX[i] = 0.0f;
        m_posY[i] = 0.0f;
    }
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
    m_isExist = false;
}

void Enemy::Update()
{
    //���݂��Ă��Ȃ��G�̏����͍s��Ȃ�
    if (!m_isExist) return;

    //�ߋ����O��������炵�Ă���
    for (int i = kPosLogFrame - 1; i >= 1; i++)
    {
        m_posX[i] = m_posX[i - 1];
        m_posY[i] = m_posY[i - 1];
    }
#if 0
    m_posX[7] = m_posX[6];
    m_posX[6] = m_posX[5];
    m_posX[5] = m_posX[4];
    m_posX[4] = m_posX[3];
    m_posX[3] = m_posX[2];
    m_posX[2] = m_posX[1];
    m_posX[1] = m_posX[0];
#endif

//    m_posY += kspeed;
    m_posY += m_moveY;
    m_moveY += 1.0f; //�ړ����x�����񂾂�傫������
    if (m_posY > Game::kScreenHeight)
    {
        //��ʊO�̏o���G���ė��p
        m_isExist = false;
    }
}

void Enemy::Draw() const
{
    //���݂��Ă��Ȃ��G�̏����͍s��Ȃ�
    if (!m_isExist) return;

    //�����ɗ�����m_handle��-1���ƃO���t�B�b�N�͐�΂ɕ\������Ȃ�(�o�O)
    assert(m_handle != -1);

    for (int i = 0; i < kPosLogFrame; i++)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - i * 32);
        DrawGraph(static_cast<int>(m_posX[i]), static_cast<int>(m_posY[i]),m_handle,false);
    }
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�ʏ�`��ɖ߂�

    DrawGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), m_handle, false);
}

void Enemy::SetGraphHandle(int handle)
{
    m_handle = handle;
    //�O���t�B�b�N�T�C�Y���擾���Ă���
    GetGraphSize(m_handle, &m_width, &m_height);
}

void Enemy::Start()
{
    m_isExist = true;
    SetStartPos(); //�����_���Ȕz�u
    m_moveY = 0.0f;
}

void Enemy::SetStartPos()
{
    //�O���t�B�b�N�̌��肪�s���Ă��Ȃ��ƓK�؂Ȉʒu���ݒ�ł��Ȃ�
    assert(m_handle != -1);
    //��ʏ㕔�����_���ȉ��ʒu�ɐݒ�
    m_posX[0] = static_cast<float>(GetRand(Game::kScreenWidth - m_width));
    m_posY[0] = 0.0f - m_height;
    if (int i = 1; i < kPosLogFrame; i++)
    {
        m_posX[i] = m_posX[0];
        m_posY[i] = m_posY[0];
    }
}

float Enemy::getLeft() const
{
    return m_posX;

}

float Enemy::getTop() const
{
    return m_posY;

}

float Enemy::getRight() const
{
    return m_posX + m_width;

}

float Enemy::getBotton() const
{
    return m_posY + m_height;
}