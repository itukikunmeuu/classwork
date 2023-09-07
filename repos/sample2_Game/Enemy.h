#pragma once

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw() const; //const�֐��̒��ł̓����o�ϐ���ύX�ł��Ȃ�

	//�O���t�B�b�N��ݒ�
	void SetHandle(int handle);
	//�����ʒu�̐ݒ�@��ʓ��Ƀ����_���ɔz�u����
	//�O���t�B�b�N�̃T�C�Y�����ĉ�ʓ��Ɏ��܂�悤�ɂ���̂�
	//sethandle�i�j���Ă���Ă�
	void SetStaetPos();
	

private:
	int m_handle;  //�O���t�B�b�N�n���h��
	int m_kGraphWidth;
	int m_kGraphHeight;

	int m_posX;
	int m_posY;

	int m_moveX;  //�ړ�����
};
