#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include <cassert>

#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneManager.h"

namespace
{
	
}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);


	//画面のサイズ変更
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//シーン
	SceneManager scene;
	scene.Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();
		
		//ゲームシーンの更新
		scene.Update();
		//ゲームシーンの描画
		scene.Draw();

		


		// 画面が切り替わるのを待つ
		ScreenFlip();


		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		while (GetNowHiPerformanceCount() - start <= 16667) {}
	}

	//事項していたシーンの終了処理
	scene.End();// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

/*
//プレイヤーと敵の当たり判定
//当たっている場合、trueを返す (return true　する)
//当たっていない場合、falseを返す(return false する)

//当たり判定
bool IsCollision(const Player& player, const Enemy& enemy) //当たったフラグ
{
	//当たり判定
	bool isCollision = true;
	//プレイヤーよりも完全に左にいる場合は当たっていない
	//プレイヤー左端よりも左に敵の右側がある場合は当たっていない
	if (player.getLeft() > enemy.getRight())
	{
		//完全に左にいるので当たっていないことを確定
		isCollision = false; //確実に当たっていないのでfalse返す
	}
	//プレイヤーよりも完全にしたにいる場合は当たっていない
	//プレイヤー下端よりも完全に敵の上橋がある場合は当たっていない
	if (player.getBotton() < enemy.getTop())
	{
		//完全に左にいるので当たっていないことを確定
		isCollision = false;//確実に当たっていないのでfalse返す
	}
	//同様に完全に右にいるパターンを取り除く
	if (player.getRight() < enemy.getLeft())
	{
		//完全に左にいるので当たっていないことを確定
		isCollision = false;//確実に当たっていないのでfalse返す
	}

	//同様に完全に上にいるパターンを取り除く
	if (player.getTop() < enemy.getBotton())
	{
		//完全に左にいるので当たっていないことを確定
		isCollision = false;//確実に当たっていないのでfalse返す
	}
	return isCollision;
}


// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);


	//画面のサイズ変更
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームシーンを準備
	int sceneNo = 0; //現在のシーンを変数で持つ
					 //0:Title 1:Main
					 //本来はenum等でやるべき
	SceneTitle sceneTitle;
	SceneMain sceneMain;

	switch (sceneNo)
	{
	case 0:
	  sceneTitle.Init();
	  break;
	case 1:
	  sceneMain.Init();
	default:
		assert(false); //存在しないシーンの番号が指定されている
		break;
	}


	//SceneResultをここから始める
	SceneResult sceneResult;
	sceneResult.Init();


	
	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();




		// 画面が切り替わるのを待つ
		ScreenFlip();

		//シーンの終了
		if (sceneMain.IsSceneEnd())
		{
			break;
		}

		// escキーでゲーム終了
//		if (CheckHitKey(KEY_INPUT_ESCAPE))
//		{
//			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

	//メモリからグラフィックの削除する
//	DeleteGraph(enemyHandle);
//	DeleteGraph(playerHandle);



	//シーンの終了処理
	sceneMain.End();// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
*/