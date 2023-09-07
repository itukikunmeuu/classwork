#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw() const;
	//�O���t�B�b�N�̎w��
	void SetGraphHandle(int handle);

	//�G�L�����N�^�[�J�n����
	//��ʏォ�痎���n�߂�
	void Start();

	//���݂��邩�`�F�b�N
	bool isExist() const { return m_isExist; }

	

	//�G�L�����N�^�[�̏����ʒu�ݒ�(�O���t�B�b�N�ݒ肵�Ă���s��)
	void SetStartPos();

	//�Z�Y�̓����蔻����Ƃ�̂ɕK�v�ȏ����擾����֐�
	float getLeft() const;//����X���W
	float getTop() const;//���Y���W
	float getRight() const;//�E��X���W
	float getBotton() const;//����Y���W

private:
	//�c���p�ɕۑ�����ʒu���̐�
	static constexpr int kPosLogFrame = 8;


private:
	int m_handle;
	//�O���t�B�b�N�̃T�C�Y
	int m_width;
	int m_height;

	//���݂��邩�t���O
	bool m_isExist;
	
	float m_posX;
	float m_posY;

	//�ړ���
	float m_moveY;
};

