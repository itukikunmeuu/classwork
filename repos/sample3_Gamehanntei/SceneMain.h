#pragma once
#include "Rect.h"
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw();
	void End();

private:
	//�N���X�̒萔��`
	//private�Ȃ̂ł��̃N���X���ł����g���Ȃ�
	static constexpr int kRectNum = 32;

private:
	Rect m_player;
	Rect m_rect[kRectNum];
};

