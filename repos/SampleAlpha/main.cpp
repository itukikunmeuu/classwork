#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	int handle = LoadGraph("hana.jpg");
	int fadeAlpha = 255; //不透明から始める
	int fadeSpeed = -1;  //透明度を高める

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理
		fadeAlpha += fadeSpeed;
		//0以下にならないようにする
		if (fadeAlpha < 0)
		{
			//完全にフェードインした
			fadeAlpha = 0;
			//次のフレームからはフェードアウト
			fadeSpeed = 1;
		}
		if (fadeAlpha > 255)
		{
			//完全にフェードアウト
			fadeAlpha = 255;
		}

		//第一引数　DX_BLENDMODE_ALPHA:　半透明で表示したい！
		//第二引数　DX_BLENDMODE_ALPHAを指定している場合
		//			どれくらいの透明度で表示するか、を指定する　0〜255
		//			0：完全に透明　255：不透明
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,fadeAlpha);
		DrawGraph(0, 0, handle, true);	//640x480の画像を表示

		//SetDrawBlendModeで透明にしたい物体を表示した後、
		//以降の物体が半透明にならないよう
		//Dx_BLENDMODE_NOBLENDに戻しておく
		//第二引数は何を指定しても同じ
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);


		//SetDrawBlendModeで半透明にしたい！と指定すると
		//以降すべてのものは同じ透明度で表示される
		DrawBox(0, 0, 640, 240, GetColor(255, 255, 0), true); //画面上半分を覆う四角

		//フェードイン　αを255から0に変化させる
		//フェード用に黒四角を表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
		DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), true); //画面上半分を覆う四角
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}