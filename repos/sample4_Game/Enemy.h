#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw() const;
	//グラフィックの指定
	void SetGraphHandle(int handle);

	//敵キャラクター開始処理
	//画面上から落ち始める
	void Start();

	//存在するかチェック
	bool isExist() const { return m_isExist; }

	

	//敵キャラクターの初期位置設定(グラフィック設定してから行う)
	void SetStartPos();

	//短刑の当たり判定をとるのに必要な情報を取得する関数
	float getLeft() const;//左のX座標
	float getTop() const;//上のY座標
	float getRight() const;//右のX座標
	float getBotton() const;//下のY座標

private:
	//残像用に保存する位置情報の数
	static constexpr int kPosLogFrame = 8;


private:
	int m_handle;
	//グラフィックのサイズ
	int m_width;
	int m_height;

	//存在するかフラグ
	bool m_isExist;
	
	float m_posX;
	float m_posY;

	//移動量
	float m_moveY;
};

