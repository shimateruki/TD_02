#include <Novice.h>
#include "struct.h"
#include "move.h"
#include "hitBox.h"
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
	int attckTimer = 0;
	int isAttckTimer = false;

	//セレクトするための変数
	int isTitle = false;
	int isReturn = true;
	
	//画像読み込み
	int playerDownImages = Novice::LoadTexture("./Resoucers/images/playerDown.png");
	int playerUpimages	 = Novice::LoadTexture("./Resoucers/images/playerUp.png");
	int playerLeftImages = Novice::LoadTexture("./Resoucers/images/playerLeft.png");
	int playerRightImages = Novice::LoadTexture("./Resoucers/images/playerRight.png");

	
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

			//spaceキーを押すとシーンがgameplayに切り替わる

			if (keys[DIK_SPACE])
			{
				scene = GAMEPLAY;
			}
			break;
		case GAMEPLAY:


		//移動処理

		playerMove(player, keys);

		//攻撃コマンドのところでspaceキーを押すとフラグがtrueになり

		if (isAttckTimer)
		{
			attckTimer++;
		}

		//タイマーが300になるとコマンドの描画を再度出現させる

		 if (attckTimer >300)
		{
			isAttckTimer = false;
			attckTimer = 0;
		}

		//プレイヤーとコマンドの当たり判定

		if (IsHitDetection(player.screenPos.x, player.screenPos.y, player.size.x, player.size.y,
			attckbutton.screenPos.x, attckbutton.screenPos.y, attckbutton.size.x, attckbutton.size.y))
		{
			if (keys[DIK_SPACE])
			{
				isAttckTimer = true;
			}
		}

			break;
		case GAMECLEAR:

			//spaceキーを押すとタイトルへ戻る
			if (keys[DIK_SPACE])
			{
				scene = TITLE;
			}

			break;
		case GAMEOVER:
			//リスタートかタイトルへ戻るかを選ぶ処理

			if (keys[DIK_A])
			{
				isReturn = false;
				isTitle = true;
			}
			else if (keys[DIK_S])
			{
				isReturn = true;
				isTitle = false;
			}

			//リスタート
			if (isReturn)
			{
				if (keys[DIK_SPACE])
				{
					scene = GAMEPLAY;
				}
			}

			//タイトルへ戻る
			else if (isTitle)
			{
				if (keys[DIK_SPACE])
				{
					scene = TITLE;
				}
			}

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

			//プレイヤーの描画

			//下向き
			if (player.isAlive &&vector ==DOWN)
			{
				Novice::DrawSprite(int(player.screenPos.x), int(player.screenPos.y), playerDownImages, 1.0f, 1.0f, 0.0f, WHITE);
			}

			//上向き
			if(player.isAlive && vector == UP)
			{
				Novice::DrawSprite(int(player.screenPos.x), int(player.screenPos.y), playerUpimages, 1.0f, 1.0f, 0.0f, WHITE);
			}

			//左向き
			if (player.isAlive && vector == LEFT)
			{
				Novice::DrawSprite(int(player.screenPos.x), int(player.screenPos.y), playerLeftImages, 1.0f, 1.0f, 0.0f, WHITE);
			}

			//右向き
			if (player.isAlive && vector == RIGHT)	
			{
				Novice::DrawSprite(int(player.screenPos.x), int(player.screenPos.y), playerRightImages, 1.0f, 1.0f, 0.0f, WHITE);
			}




		

			//プレイヤーの攻撃コマンド描画

			if (!isAttckTimer)
			{
				Novice::DrawBox(int(attckbutton.screenPos.x), int(attckbutton.screenPos.y), int(attckbutton.size.x), int(attckbutton.size.y), 0.0f, WHITE, kFillModeSolid);
			}
		
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
