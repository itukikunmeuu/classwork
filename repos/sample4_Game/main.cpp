#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include <cassert>

#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneManager.h"

namespace
{
	
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);


	//��ʂ̃T�C�Y�ύX
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//�V�[��
	SceneManager scene;
	scene.Init();

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();
		
		//�Q�[���V�[���̍X�V
		scene.Update();
		//�Q�[���V�[���̕`��
		scene.Draw();

		


		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();


		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		while (GetNowHiPerformanceCount() - start <= 16667) {}
	}

	//�������Ă����V�[���̏I������
	scene.End();// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

/*
//�v���C���[�ƓG�̓����蔻��
//�������Ă���ꍇ�Atrue��Ԃ� (return true�@����)
//�������Ă��Ȃ��ꍇ�Afalse��Ԃ�(return false ����)

//�����蔻��
bool IsCollision(const Player& player, const Enemy& enemy) //���������t���O
{
	//�����蔻��
	bool isCollision = true;
	//�v���C���[�������S�ɍ��ɂ���ꍇ�͓������Ă��Ȃ�
	//�v���C���[���[�������ɓG�̉E��������ꍇ�͓������Ă��Ȃ�
	if (player.getLeft() > enemy.getRight())
	{
		//���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ƃ��m��
		isCollision = false; //�m���ɓ������Ă��Ȃ��̂�false�Ԃ�
	}
	//�v���C���[�������S�ɂ����ɂ���ꍇ�͓������Ă��Ȃ�
	//�v���C���[���[�������S�ɓG�̏㋴������ꍇ�͓������Ă��Ȃ�
	if (player.getBotton() < enemy.getTop())
	{
		//���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ƃ��m��
		isCollision = false;//�m���ɓ������Ă��Ȃ��̂�false�Ԃ�
	}
	//���l�Ɋ��S�ɉE�ɂ���p�^�[������菜��
	if (player.getRight() < enemy.getLeft())
	{
		//���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ƃ��m��
		isCollision = false;//�m���ɓ������Ă��Ȃ��̂�false�Ԃ�
	}

	//���l�Ɋ��S�ɏ�ɂ���p�^�[������菜��
	if (player.getTop() < enemy.getBotton())
	{
		//���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ƃ��m��
		isCollision = false;//�m���ɓ������Ă��Ȃ��̂�false�Ԃ�
	}
	return isCollision;
}


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);


	//��ʂ̃T�C�Y�ύX
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//�Q�[���V�[��������
	int sceneNo = 0; //���݂̃V�[����ϐ��Ŏ���
					 //0:Title 1:Main
					 //�{����enum���ł��ׂ�
	SceneTitle sceneTitle;
	SceneMain sceneMain;

	switch (sceneNo)
	{
	case 0:
	  sceneTitle.Init();
	  break;
	case 1:
	  sceneMain.Init();
	default:
		assert(false); //���݂��Ȃ��V�[���̔ԍ����w�肳��Ă���
		break;
	}


	//SceneResult����������n�߂�
	SceneResult sceneResult;
	sceneResult.Init();


	
	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();




		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		//�V�[���̏I��
		if (sceneMain.IsSceneEnd())
		{
			break;
		}

		// esc�L�[�ŃQ�[���I��
//		if (CheckHitKey(KEY_INPUT_ESCAPE))
//		{
//			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

	//����������O���t�B�b�N�̍폜����
//	DeleteGraph(enemyHandle);
//	DeleteGraph(playerHandle);



	//�V�[���̏I������
	sceneMain.End();// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
*/