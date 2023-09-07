#pragma once
#include "Player.h"
class SceneMain
{
public:
	SceneMain();  //コンストラクタ メモリが確保されたときに呼ばれる関数
	~SceneMain(); //デストラクタ　メモリが解放されるときに呼ばれる関数

	void Init();
	void Update();
	void Draw() const; //関数にconstをつけることでその関数の内部で
					   //メンバー変数を変更できなくなる
private:
	//たくさん表示する
	static constexpr int kPlayerNum = 65536;


private:

	int m_frameCount;

	Player m_player[kPlayerNum];
	Player* m_pPlayer;
};

