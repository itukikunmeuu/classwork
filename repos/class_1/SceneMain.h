#pragma once
#include "Player.h"
class SceneMain
{
public:
	SceneMain();  //�R���X�g���N�^ ���������m�ۂ��ꂽ�Ƃ��ɌĂ΂��֐�
	~SceneMain(); //�f�X�g���N�^�@����������������Ƃ��ɌĂ΂��֐�

	void Init();
	void Update();
	void Draw() const; //�֐���const�����邱�Ƃł��̊֐��̓�����
					   //�����o�[�ϐ���ύX�ł��Ȃ��Ȃ�
private:
	//��������\������
	static constexpr int kPlayerNum = 65536;


private:

	int m_frameCount;

	Player m_player[kPlayerNum];
	Player* m_pPlayer;
};

