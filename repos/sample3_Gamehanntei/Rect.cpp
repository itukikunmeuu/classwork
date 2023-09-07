#include "Rect.h"
#include "DxLib.h"

namespace
{
	//ランダムに生成する短形のサイズ制限
	constexpr int kWidthMin = 32; //最小幅
	constexpr int kWidthMax = 128; //最大幅

	constexpr int kHeightMin = 24; //最小幅
	constexpr int kHeightMax = 96; //最大幅
}

Rect::Rect():
	m_posX(320),
	m_posY(240),
	m_width(64),
	m_height(64),
	m_color(GetColor(255,255,255)),
	m_isFill(false),
	m_isMouseTrase(false)
{
}

Rect::~Rect()
{
}

void Rect::Init()
{
}

void Rect::Update()
{
	//マウス追従グラフ
	if (m_isMouseTrase)
	{
		GetMousePoint(&m_posX, &m_posY);
	}
}

void Rect::Draw()
{
	//中心座標と短形の幅、高さから左上のＸＹ座標、右下のＸＹ座標を求める
	int leftX = m_posX - m_width / 2;
	int rightX = m_posX + m_width / 2;
	int topX = m_posY - m_height / 2;
	int bottomY = m_posY + m_height / 2;

	DrawBox(GetLeft(), GetTop(),	//右上の座標
		GetRight(), GetBottom(),	//右下の座標
		m_color, m_isFill);
}

void Rect::SetRandom()
{
	m_posX = GetRand(640);
	m_posY = GetRand(480);
	m_width = GetRand(kWidthMax - kWidthMin) + kWidthMin;
	m_height = GetRand(kHeightMax - kHeightMin) + kHeightMin;
}

bool Rect::IsCollision(const Rect& target) const
{
	//rect0の完全に左にいる場合は当たっていない
	if (GetLeft() > target.GetRight())
	{
		return false;

	}
	//rect0の完全にしたにいる場合は当たってない
	if (GetBottom() < target.GetTop())
	{
		return false;
	}
	//rect0の完全に右にいる場合は当たっていない
	if (GetRight() < target.GetLeft())
	{
		return false;
	}
	//rect0の完全に上にいる場合は当たっていない
	if (GetTop() > target.GetBottom())
	{
		return false;
	}
	//完全に当たっていないパターンを取り除いて
	//残った奴は当たっている
	return true;
}

int Rect::GetLeft() const
{
	return m_posX - m_width / 2;
}

int Rect::GetTop() const
{
	return m_posY - m_width / 2;
}

int Rect::GetRight() const
{
	return m_posX + m_height / 2;
}

int Rect::GetBottom() const
{
	return m_posY + m_height / 2;
}
