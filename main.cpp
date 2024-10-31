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

	Player player;
	player.pos = { 600, 400 };
	player.size = { 32.0f, 32.0f };
	player.speed = 5;

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
			break;
		case GAMEPLAY:
			Novice::DrawBox(int(player.pos.x), int(player.pos.y), int(player.size.x), int(player.size.y), 0.0f, WHITE, kFillModeSolid);
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
			break;
		case GAMEPLAY:
			Novice::DrawBox(int(player.pos.x), int(player.pos.y), int(player.size.x), int(player.size.y), 0.0f, WHITE, kFillModeSolid);
			break;
		case GAMECLEAR:
			break;
		case GAMEOVER:
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
