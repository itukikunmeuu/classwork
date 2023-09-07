#pragma once
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void Update();
	void Draw();
	void End();

private:
	static constexpr int kBgNum = 4;

private:

	int m_bgHandle[kBgNum]; //bg -> background �w�i�̗���
	int m_bgNo;				//���ݕ\�����Ă���BG�̔ԍ�
	
	int m_fadeCount; //�t�F�[�h�̓x�����@0:�����t�F�[�h�C�������������(�Q�[����ʂ������Ă���)
	                 //				   255:�s�����A�t�F�[�h�A�E�g�����������


	int m_fadeSpeed; //�t�F�[�h���x
	int m_waitFrame; //�t�F�[�h�C������������̑҂�����

};

