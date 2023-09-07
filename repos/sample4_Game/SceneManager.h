#pragma once
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneResult.h"
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void End();

private:
	//�萔�̒�`
	enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindMain,
		kSceneKindResult
	};
	int Num = 4;

private:
	//���ݎ��s���̃V�[��
	SceneKind m_runScene;

	//SceneManager�ŊǗ�����e�V�[��
	SceneTitle m_title;
	SceneMain m_main;
	SceneResult m_result;
	
	int m_bgNo;
	int m_fadeCount;
	int m_fadeSpeed;
	int m_waitFrame;
};

