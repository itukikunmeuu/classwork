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

	int m_bgHandle[kBgNum]; //bg -> background 背景の略称
	int m_bgNo;				//現在表示しているBGの番号
	
	int m_fadeCount; //フェードの度合い　0:透明フェードインしきった状態(ゲーム画面が見えている)
	                 //				   255:不透明、フェードアウトしきった状態


	int m_fadeSpeed; //フェード速度
	int m_waitFrame; //フェードインしきった後の待ち時間

};

