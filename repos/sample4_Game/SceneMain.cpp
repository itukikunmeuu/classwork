#include "SceneMain.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace
{
	//�Q�[���I�[�o�[���ɕ\�����镶����
	const char* const kGameOverString = "�Q�[���I�[�o�[";

	//�G�̏����������o(�t���[����)
	constexpr int kEnemyWaitDefault = 60;
	//�G�̍ŒZ�������o
	constexpr int kEnemyWaitFrameMin = 3;
	//�G�̂��������񂩂�����I�Ȃ���������邽�тɒZ�����邩
	constexpr int kEnemyWaitFrameChangeNum = 5;
	//��x�������o��Z������Ƃ��ɉ��t���[���Z�����邩
	constexpr int kEnemyWaitFrameChangeFrame = 2;
	
}

SceneMain::SceneMain() :
	m_playerHandle(-1),
	m_enemyHandle(-1),
	m_player(), //�N���X������������Ƃ��A()�̒��ɂ̓R���X�g���N�^�̈���������
	//player�N���X�Ɋւ��Ă̓R���X�g���N�^�Ɉ������Ȃ��̂�()��OK
	m_enemy(),
	m_isGaneOver(false),
	m_isSceneEnd(false),
	m_playFrameCount(0),
	m_enemyCreateNum(0),
	m_enrmyWaitFrame(0),
	m_bgmHandle(-1),
	m_fadeAlpha(255)  //�s�����ŏ�����
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	ChangeFont("HGP�s����");
	SetFontSize(48);

	//�O���t�B�b�N�̃��[�h
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);  //�O���t�B�b�N�̃��[�h�Ɏ��s���Ă�������~�߂�
	m_enemyHandle = LoadGraph("data/image/enemy.png");
	assert(m_enemyHandle != -1);  //�O���t�B�b�N�̃��[�h�Ɏ��s���Ă�������~�߂�

	//�T�E���h�̃��[�h
	m_bgmHamdle = LoadSoundMem("data/image/Main.mp3");
	m_enemyStaetSe = LoadSoundMem("data/image/enemy.mp3");
	//BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	//�t�F�[�h�C�������邽�߉���0����n�߂�
	ChangeVolumeSoundMem(0, m_bgmHandle);

	//�v���C���[�̏�����
	m_player.Init();
	m_player.SetGraphHandle(m_playerHandle);
	//�G�̏�����
	for (int i = 0; i < kEnemyMax; i++)
	{
	m_enemy[i].Init();
	m_enemy[i].SetGraphHandle(m_enemyHandle);
	m_enemy[i].SetStartPos(); //�O���t�B�b�N��ݒ肵���㏉���l�ɐݒ�
	}

	m_isGaneOver = false;
	m_isSceneEnd = false;
	m_playFrameCount = 0;
	m_enemyCreateNum = 0;

	m_fadeAlpha = 255;
}

void SceneMain::Update()
{
	//�Q�[���I�[�o�[�ɂȂ�����e�������s�킸�A��Update()���I��������
	if (m_isGaneOver) 
	{
		if (m_isSceneEnd)
		{
			//�t�F�[�h�A�E�g
			m_fadeAlpha += 8;
				if (m_fadeAlpha > 255)
				{
					m_fadeAlpha = 255;
				}
		}
		//1�{�^��orZ�L�[�������ꂽ��Q�[���I�[�o�[��ʂ�
		int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (pad & PAD_INPUT_1)  //1�{�^���������ꂽ
		{
			m_isSceneEnd = true;
		}
		return;
	
	}
	//�t�F�[�h�C��
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	//�����c�莞�ԁi�t���[�����j�𑝂₷
	m_playFrameCount++;

	m_player.Update();
	for (int i = 0; i < kEnemyMax; i++)
	{
		m_enemy[i].Update();
		if (IsCollision(m_player, m_enemy[i]))
		{
			m_isGaneOver = true;
		}

	}
	//���Ԋu�œG�𐶐�
	m_enrmyWaitFrame++;
	//�G5�̐������邽�тɓG�̐������o��1�t���[���Z���Ȃ�
	int waitFrame = kEnemyWaitDefault;
	waitFrame -= (m_enemyCreateNum / 5) * 1;
	//��ԒZ����3�t���[�����o
	if (waitFrame < 3) waitFrame = 3;

	if (m_enrmyWaitFrame >= waitFrame)
	{
		//���ݎg���Ă��Ȃ��G�L�����N�^�[��T����
		//������Staet������
		for (int i = 0; i < kEnemyMax; i++)
		{
			//m_enemy[i].isExist()��false�̏ꍇ���݂��Ă��Ȃ�
			//�̂ł������g��
			if (!m_enemy[i].isExist())
			{
				m_enrmyWaitFrame = 0;
				m_enemyCreateNum++;
				m_enemy[i].Start();

				//���ʉ��𗬂�
				PlaySoundMem(m_enemyStaetSe, DX_PLAYTYPE_BACK);
				break; //1�̐���������I��
			}
		}
	}
}

void SceneMain::Draw()
{
	m_player.Draw();
	for (int i = 0; i < kEnemyMax; i++)
	{
	m_enemy[i].Draw();
	}

	//�������Ԃ�\��
	//��:�b.�~���b
//	int sec = m_playFrameCount / 60;
	int milliSec = m_playFrameCount * 1000 / 60;
	int sec = (milliSec / 1000) % 60;
	int min = (milliSec / 1000) / 60;
	milliSec %= 1000; //�~���b�̕����̂ݎc��
	//������̉����擾
	int strWidth = GetDrawFormatStringWidth("%3d:%02d:%03d", min, sec, milliSec);

	DrawFormatString(Game::kScreenWidth/2, 8, GetColor(255, 255, 255),
		"%3d:%02d:%03d", min, sec, milliSec);

	for (int i = 0; i < kEnemyMax; i++)
	{
		if (IsCollision(m_player, m_enemy[i]))
		{
			//��ʒ����ɃQ�[���I�[�o�[�\��

			//�\�����镶���̉������擾����
			//GetDrawStringWidth(char * strung, int strLen);
			int len = strlen(kGameOverString);
			int width = GetDrawStringWidth("�Q�[���I�[�o�[", len);
			int height = GetFontSize();
			//�������Ă��邩�ǂ������m�F����f�o�b�O�\��
			DrawString(Game::kScreenWidth / 2 - width / 2,
				Game::kScreenHeight / 2 - height / 2,
				"�Q�[���I�[�o�[", GetColor(255, 32, 32));
		}
	}
	//�t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha); //�������ŕ\���J�n
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255),true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

bool SceneMain::IsCollision(const Player& player, const Enemy& enemy)
{
	//���݂��Ȃ��G�Ƃ͓�����Ȃ�
	if (!enemy.isExist()) return false;

	//�����蔻��

	//�v���C���[�������S�ɍ��ɂ���ꍇ�͓������Ă��Ȃ�
	//�v���C���[���[�������ɓG�̉E��������ꍇ�͓������Ă��Ȃ�
	if (player.getLeft() > enemy.getRight())
	{
		//���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ƃ��m��
		return false; //�m���ɓ������Ă��Ȃ��̂�false�Ԃ�
	}
	//�v���C���[�������S�ɂ����ɂ���ꍇ�͓������Ă��Ȃ�
	//�v���C���[���[�������S�ɓG�̏㋴������ꍇ�͓������Ă��Ȃ�
	if (player.getBotton() < enemy.getTop())
	{
		//���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ƃ��m��
		return false;//�m���ɓ������Ă��Ȃ��̂�false�Ԃ�
	}
	//���l�Ɋ��S�ɉE�ɂ���p�^�[������菜��
	if (player.getRight() < enemy.getLeft())
	{
		//���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ƃ��m��
		return false;//�m���ɓ������Ă��Ȃ��̂�false�Ԃ�
	}

	//���l�Ɋ��S�ɏ�ɂ���p�^�[������菜��
	if (player.getTop() > enemy.getBotton())
	{
		//���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ƃ��m��
		return false;//�m���ɓ������Ă��Ȃ��̂�false�Ԃ�
	}
	return true;
}


void SceneMain::End()
{
	//����������O���t�B�b�N�̍폜����
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_playerHandle);
	//����������T�E���h���폜
	DeleteSoundMem(m_enemyStaetSe);
}