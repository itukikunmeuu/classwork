#include "DxLib.h"
#include "SceneMain.h"

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

	//メモリを明示的に確保する
	//newを使用してメモリを確保することで
	//ヒープ領域にメモリを確保することができる
	//
	//newはメモリを確保し、どこにメモリを確保したか、の
	//アドレスを返してくれる
	SceneMain* pMain = new SceneMain;
	pMain->Init();

	//SceneMain sceneMain;
	//sceneMain.Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理
		pMain->Update();

		pMain->Draw();

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

	//確保したメモリを開放する
	delete pMain;
	pMain = nullptr;

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}