#include "Player.h"
#include "DxLib.h"

Player::Player():
	m_x(GetRand(640)),
	m_y(GetRand(480))
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
}

void Player::Draw() const
{
	DrawCircle(m_x, m_y, 32, GetColor(255, 255, 0), true);
}
