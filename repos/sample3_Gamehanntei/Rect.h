#pragma once
class Rect
{
public:
	Rect();
	~Rect();

	void Init();
	void Update();
	void Draw();
	
	//画面内のランダムな位置にランダムな大きさの短形データを設定する
	void SetRandom();
	
	//ほかの句毛糸の当たり判定
	//自信と指定したほかの矩形の当たり判定をとる
	bool IsCollision(const Rect& target) const;

	//publicな関数経由でメンバー変数を変更
	void SetColor(unsigned int color) { m_color = color; }
	void SetFill(bool isFill)  {m_isFill = isFill;}
	void SetMouseTrase(bool isTrase) { m_isMouseTrase = isTrase; }

	//クラス外から座標を変更する
//	void SetposX(int x) { m_posX = x; }
//	void SetPosY(int y) { m_posY = y; }

	//当たり判定実装用に上下左右を取得できるようにする
	int GetLeft() const;		//X座標
	int GetTop() const;			//Y座標
	int GetRight() const;		//X座標
	int GetBottom() const;		//Y座標

private:
	//中心座標と幅、高さで管理する
	int m_posX;  //m_centerXみたいなのがいいかも
	int m_posY;
	int m_width;
	int m_height;

	//色
	unsigned int m_color;
	//塗りつぶしフラグ
	bool m_isFill;

	//マウス追従フラグ
	bool m_isMouseTrase;
};

