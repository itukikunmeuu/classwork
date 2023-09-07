#include "Enemy.h"
#include<cassert>
#include "DxLib.h"

namespace
{
	//移動速度
	constexpr int kMoveSpeed = 4;

}

//コンストラクタ
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

//デストラクタ
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
	//使用するグラフィックのサイズを取得する
	GetGraphSize(m_handle,&m_kGraphWidth,&m_kGraphHeight);
	
}
void Enemy::SetStaetPos()
{
	//グラフィックのサイズが決定していないと
	//画面買いに表示されるかも

	//グラフィックを決定する前に呼ばれていたらそれに気づくようにしたい
	//グラフィックが決まる前にここに来たら止まるようにしたい
	//assert(止まらない条件)
	assert(m_hamdle != -1);
	m_posX = GetRand(640 - m_kGraphWidth);
	m_posY = GetRand(640 - m_kGraphHeight);
}