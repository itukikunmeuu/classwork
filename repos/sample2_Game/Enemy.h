#pragma once

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw() const; //const関数の中ではメンバ変数を変更できない

	//グラフィックを設定
	void SetHandle(int handle);
	//初期位置の設定　画面内にランダムに配置する
	//グラフィックのサイズを見て画面内に収まるようにするので
	//sethandle（）してから呼ぶ
	void SetStaetPos();
	

private:
	int m_handle;  //グラフィックハンドル
	int m_kGraphWidth;
	int m_kGraphHeight;

	int m_posX;
	int m_posY;

	int m_moveX;  //移動方向
};
