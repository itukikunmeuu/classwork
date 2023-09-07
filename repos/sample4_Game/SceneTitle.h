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

	int m_bgmHandle;

	//�V�[�����I������������
	bool IsSceneEnd() const;

private:

	bool m_isSceneEnd; //�V�[���I���t���O
				  //true�@�^�C�g�����I�����ăQ�[����

	//���ʉ��̃n���h��
	int m_decideSe;

	int m_fadeAlpha;
};

