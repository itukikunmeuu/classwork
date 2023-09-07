#pragma once
class Rect
{
public:
	Rect();
	~Rect();

	void Init();
	void Update();
	void Draw();
	
	//��ʓ��̃����_���Ȉʒu�Ƀ����_���ȑ傫���̒Z�`�f�[�^��ݒ肷��
	void SetRandom();
	
	//�ق��̋�ю��̓����蔻��
	//���M�Ǝw�肵���ق��̋�`�̓����蔻����Ƃ�
	bool IsCollision(const Rect& target) const;

	//public�Ȋ֐��o�R�Ń����o�[�ϐ���ύX
	void SetColor(unsigned int color) { m_color = color; }
	void SetFill(bool isFill)  {m_isFill = isFill;}
	void SetMouseTrase(bool isTrase) { m_isMouseTrase = isTrase; }

	//�N���X�O������W��ύX����
//	void SetposX(int x) { m_posX = x; }
//	void SetPosY(int y) { m_posY = y; }

	//�����蔻������p�ɏ㉺���E���擾�ł���悤�ɂ���
	int GetLeft() const;		//X���W
	int GetTop() const;			//Y���W
	int GetRight() const;		//X���W
	int GetBottom() const;		//Y���W

private:
	//���S���W�ƕ��A�����ŊǗ�����
	int m_posX;  //m_centerX�݂����Ȃ̂���������
	int m_posY;
	int m_width;
	int m_height;

	//�F
	unsigned int m_color;
	//�h��Ԃ��t���O
	bool m_isFill;

	//�}�E�X�Ǐ]�t���O
	bool m_isMouseTrase;
};

