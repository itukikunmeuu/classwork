#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	int handle = LoadGraph("hana.jpg");
	int fadeAlpha = 255; //�s��������n�߂�
	int fadeSpeed = -1;  //�����x�����߂�

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
		fadeAlpha += fadeSpeed;
		//0�ȉ��ɂȂ�Ȃ��悤�ɂ���
		if (fadeAlpha < 0)
		{
			//���S�Ƀt�F�[�h�C������
			fadeAlpha = 0;
			//���̃t���[������̓t�F�[�h�A�E�g
			fadeSpeed = 1;
		}
		if (fadeAlpha > 255)
		{
			//���S�Ƀt�F�[�h�A�E�g
			fadeAlpha = 255;
		}

		//�������@DX_BLENDMODE_ALPHA:�@�������ŕ\���������I
		//�������@DX_BLENDMODE_ALPHA���w�肵�Ă���ꍇ
		//			�ǂꂭ�炢�̓����x�ŕ\�����邩�A���w�肷��@0�`255
		//			0�F���S�ɓ����@255�F�s����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,fadeAlpha);
		DrawGraph(0, 0, handle, true);	//640x480�̉摜��\��

		//SetDrawBlendMode�œ����ɂ��������̂�\��������A
		//�ȍ~�̕��̂��������ɂȂ�Ȃ��悤
		//Dx_BLENDMODE_NOBLEND�ɖ߂��Ă���
		//�������͉����w�肵�Ă�����
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);


		//SetDrawBlendMode�Ŕ������ɂ������I�Ǝw�肷���
		//�ȍ~���ׂĂ̂��͓̂��������x�ŕ\�������
		DrawBox(0, 0, 640, 240, GetColor(255, 255, 0), true); //��ʏ㔼���𕢂��l�p

		//�t�F�[�h�C���@����255����0�ɕω�������
		//�t�F�[�h�p�ɍ��l�p��\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
		DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), true); //��ʏ㔼���𕢂��l�p
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}