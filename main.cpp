#include <Novice.h>
#include "struct.h"
#include "move.h"
const char kWindowTitle[] = "LC1C_09_シマ_テルキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//シーン

	enum Scene
	{
		TITLE, 
		GAMEPLAY,
		GAMECLEAR,
		GAMEOVER,
	};
	int scene = TITLE;
	//プレイヤーの描画

	Box player;
	player.screenPos = { 600, 400 };
	player.size = { 32.0f, 32.0f };
	player.velocity = { 5, 5 };
	player.isAlive = true;

	//攻撃コマンドの変数
	Box attckbutton;
	attckbutton.screenPos = { 550.0f, 550.0f };
	attckbutton.size = { 200.0f, 100.0f };


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		
		//プレイヤーの移動の関数
		
		switch (scene)
		{
		case TITLE:
			if (keys[DIK_SPACE])
			{
				scene = GAMEPLAY;
			}
			break;
		case GAMEPLAY:

		playerMove(player, keys);
	
			
			break;
		case GAMECLEAR:
			break;
		case GAMEOVER:
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		//プレイヤーの描画
		switch (scene)
		{
		case TITLE:
			Novice::ScreenPrintf(0, 0, "title");
			break;
		case GAMEPLAY:

			//プレイヤーの描画

			if (player.isAlive)
			{
				Novice::DrawBox(int(player.screenPos.x), int(player.screenPos.y), int(player.size.x), int(player.size.y), 0.0f, WHITE, kFillModeSolid);
			}
			Novice::ScreenPrintf(0, 0, "play");

			//プレイヤーの攻撃コマンド描画

			Novice::DrawBox(int(attckbutton.screenPos.x), int(attckbutton.screenPos.y), int(attckbutton.size.x), int(attckbutton.size.y),0.0f, WHITE, kFillModeSolid);
	
			break;
		case GAMECLEAR:
			Novice::ScreenPrintf(0, 0, "clear");
			break;
		case GAMEOVER:
			Novice::ScreenPrintf(0, 0, "over");
			break;
		}
		

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
