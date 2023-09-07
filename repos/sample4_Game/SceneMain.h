#pragma once
#include "Player.h"
#include "Enemy.h"

//�Q�[���V�[�����N���X������
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw();
	void End();

	//�V�[�����I�������邩�ǂ���
	bool IsSceneEnd() const;

	bool IsCollision(const Player& player, const Enemy& enemy);

private:
	//��ʓ��ɓ����ɑ��݂ł���G�̍ő吔
	static constexpr int kEnemyMax = 16;

private:
	int m_playerHandle; //�v���C���[�̃O���t�B�b�N
	int m_enemyHandle; //�G�̃O���t�B�b�N

	int m_bgmHandle;
	int m_enemyStaetSe;//�G���o�ꂷ��Ƃ��̌��ʉ�

	Player m_player;
	Enemy m_enemy[kEnemyMax];

	bool m_isGaneOver;	      //�Q�[���I�[�o�[���ǂ����̃t���O
	bool m_isSceneEnd;		  //�V�[�����I������Ƃ�true�ɂ���
	int m_playFrameCount;	  //�����c���Ă��鎞��

	//Enemy�̐�������
	int m_enemyCreateNum; //���܂łɐ��������G�̐�
	int m_enrmyWaitFrame; //�G�����܂ł̑҂�����

	//�t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

};

