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

	//シーンを終了させたいか
	bool IsSceneEnd() const;

private:

	bool m_isSceneEnd; //シーン終了フラグ
				  //true　タイトルを終了してゲームへ

	//効果音のハンドル
	int m_decideSe;

	int m_fadeAlpha;
};

