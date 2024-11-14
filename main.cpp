#include <Novice.h>
#include <cmath>
#include "struct.h"
#include "move.h"
#include "hitBox.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>




const char kWindowTitle[] = "LC1C_09_シマ_テルキ_タイトル";

float degToRad(float degrees) {
	return degrees * (3.14159265358979323846f / 180.0f);
}

// ベクトルの長さを計算
float length(Vector2 v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}

// ベクトルを正規化
Vector2 normalize(Vector2 v) {
	float len = length(v);
	return { v.x / len, v.y / len };
}


#pragma region 第一形態に使うボスの関数
// 散弾の関数//
void shotgunBullets(EnemyAttack bullets[],  Enemy& mob, const int kBulletMax, float theta) {
	if (mob.attackPattern == 1) {
		// 弾の発射クールタイムの管理
		if (!mob.isBulletCool) {
			mob.shootCoolTime++;
		}

		// クールタイムが30フレームを超えたら弾の発射を可能にする
		if (mob.shootCoolTime >= 15) {
			mob.shootCoolTime = 0;
			mob.isBulletCool = true;
		}

		// 散弾を発射する条件
		if (mob.isBulletCool) {
			const int bulletCount = 7;       // 散弾の数
			const float spreadAngle = 40.0f; // 散弾の広がり角度
			float angleStep = spreadAngle / (bulletCount - 1); // 各弾の間隔角度

			// 散弾を発射するループ
			for (int j = 0; j < bulletCount; j++) {
				for (int i = 0; i < kBulletMax; i++) {

					// 未発射の弾を見つける
					if (bullets[i].isBulletShoot == 0) {
						bullets[i].isBulletShoot = 1; // 弾を発射
						mob.isBulletCool = false; // 発射クールタイムをリセット
						bullets[i].pos.x = mob.screenPos.x + (mob.size.x / 2);
						bullets[i].pos.y = mob.screenPos.y + (mob.size.y / 2);

						// 発射する角度を計算
						float angle = -spreadAngle + theta + j * angleStep; // 発射角度
						bullets[i].velocity.x = cos(degToRad(angle)) * 5.0f; // x方向の速度
						bullets[i].velocity.y = sin(degToRad(angle)) * 5.0f; // y方向の速度
						break; // 弾を発射したら内側のループを抜ける
					}
				}
			}
		}
	}

	// 弾の移動処理
	for (int i = 0; i < kBulletMax; i++) {
		if (bullets[i].isBulletShoot == 1) {
			bullets[i].pos.x += bullets[i].velocity.x; // x座標を更新
			bullets[i].pos.y += bullets[i].velocity.y; // y座標を更新

			// 画面外に出たら弾を無効化
			if (bullets[i].pos.y > 720.0f || bullets[i].pos.x < 0 || bullets[i].pos.x > 1280.0f) {
				bullets[i].isBulletShoot = 0; // 無効化
			}
		}
	}
}

//上から降ってくる乱数弾の処理//
void randUpBullets(EnemyAttack bullets[],  Enemy& mob, const int kBulletMax) {
	if (mob.attackPattern == 2) {
		// 弾の発射クールタイムの管理
		if (!mob.isBulletCool) {
			mob.shootCoolTime++;
		}

		// クールタイムが30フレームを超えたら弾の発射を可能にする
		if (mob.shootCoolTime >= 10) {
			mob.shootCoolTime = 0;
			mob.isBulletCool = true;
		}
		if (mob.isBulletCool) {
			for (int i = 0; i < kBulletMax; i++) {


				if (bullets[i].isBulletShoot == 0) {
					bullets[i].isBulletShoot = 1; // 弾を発射
					mob.isBulletCool = false; // 発射クールタイムをリセット
					bullets[i].pos.x = float(rand() % 1250);
					bullets[i].pos.y = 150;
					break;
				}
			}
		}
	}





	// 弾の移動処理
	for (int i = 0; i < kBulletMax; i++) {
		if (bullets[i].isBulletShoot == 1) {
			bullets[i].frame++;
			if (bullets[i].frame < 15) {
				bullets[i].pos.x += bullets[i].velocity.x; // x座標を更新
			} else if (bullets[i].frame < 30) {
				bullets[i].pos.x -= bullets[i].velocity.x; // x座標を更新
			} else
			{
				bullets[i].frame = 0;
			}


			bullets[i].pos.y += bullets[i].velocity.y; // y座標を更新

			// 画面外に出たら弾を無効化
			if (bullets[i].pos.y > 720.0f || bullets[i].pos.x < 0 || bullets[i].pos.x > 1280.0f) {
				bullets[i].isBulletShoot = 0; // 無効化
			}
		}

	}

}

// 誘導弾の関数//
//void homingBullets(EnemyAttack bullets[],  bossSecond& mob, const int kBulletMax) {
//
//};

//跳ねる弾//
//void bounceBullets() {
//};




//左右から飛んでくる弾//
void randLeftRightBullets(EnemyAttack bullets[],  Enemy& mob, const int kBulletMax) {
	if (mob.attackPattern == 3) {
		// 弾の発射クールタイムの管理
		if (!mob.isBulletCool) {
			mob.shootCoolTime++;
		}

		// クールタイムが30フレームを超えたら弾の発射を可能にする
		if (mob.shootCoolTime >= 13) {
			mob.shootCoolTime = 0;
			mob.isBulletCool = true;
		}
		if (mob.isBulletCool) {
			for (int i = 0; i < (kBulletMax / 2); i++) {


				if (bullets[i].isBulletShoot == 0) {
					bullets[i].isBulletShoot = 1; // 弾を発射
					mob.isBulletCool = false; // 発射クールタイムをリセット
					bullets[i].pos.x = 0;
					bullets[i].pos.y = float(rand() % 720 + 200);
					break;
				}
			}
			for (int i = (kBulletMax / 2); i < kBulletMax; i++) {
				if (bullets[i].isBulletShoot == 0) {
					bullets[i].isBulletShoot = 1; // 弾を発射
					mob.isBulletCool = false; // 発射クールタイムをリセット
					bullets[i].pos.x = 1280;
					bullets[i].pos.y = float(rand() % 720 + 200);
					break;
				}
			}
		}
	}




	// 弾の移動処理
	for (int i = 0; i < (kBulletMax / 2); i++) {
		if (bullets[i].isBulletShoot == 1) {
			bullets[i].pos.x += bullets[i].velocity.x;
		}
	}
	for (int i = (kBulletMax / 2); i < kBulletMax; i++) {
		if (bullets[i].isBulletShoot == 1) {
			bullets[i].pos.x -= bullets[i].velocity.x; // y座標を更新
		}
	}

	for (int i = 0; i < kBulletMax; i++)
	{
		// 画面外に出たら弾を無効化
		if (bullets[i].pos.y > 720.0f || bullets[i].pos.x < 0 || bullets[i].pos.x > 1280.0f) {
			bullets[i].isBulletShoot = 0; // 無効化
		}
	}



}


//画面制限の攻撃の関数//
void externaLlimitAttck(EnemyAttack bullets[],  Enemy& mob, const int kBulletMax) {

	if (mob.attackPattern == 3) {


		// 弾の発射クールタイムの管理
		if (!mob.isBulletCool) {
			mob.shootCoolTime++;
		}

		// クールタイムが30フレームを超えたら弾の発射を可能にする
		if (mob.shootCoolTime >= 10) {
			mob.shootCoolTime = 0;
			mob.isBulletCool = true;
		}
		if (mob.isBulletCool) {
			for (int i = 0; i < kBulletMax; i++) {


				if (bullets[i].isBulletShoot == 0) {
					bullets[i].isBulletShoot = 1; // 弾を発射
					mob.isBulletCool = false; // 発射クールタイムをリセット
					bullets[i].pos.x = float(rand() % 1250);
					bullets[i].pos.y = 150;
					break;
				}
			}
		}
	}





	// 弾の移動処理
	for (int i = 0; i < kBulletMax; i++) {
		if (bullets[i].isBulletShoot == 1) {
			bullets[i].frame++;
			bullets[i].pos.x += bullets[i].velocity.x;
			bullets[i].pos.y += bullets[i].velocity.y; // y座標を更新

			// 画面外に出たら弾を無効化
			if (bullets[i].pos.y > 720.0f || bullets[i].pos.x < 0 || bullets[i].pos.x > 1280.0f) {
				bullets[i].isBulletShoot = 0; // 無効化
			}
		}

	}

}

#pragma endregion

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//windowsのサイズの変数
	float windowsHeight = 720.0f;
	float windowsWidth = 1280.0f;
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, int(windowsWidth), int(windowsHeight));

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };



	int scene = TITLE;
	int vector = UP;

	int isTutorial = false;
	int isStart = false;

#pragma region プレイヤーの変数
	//playerの変数

	Box player;
	{
		player.pos = { 600, 400 };//プレイヤーの変数
		player.size = { 32.0f, 32.0f };
		player.velocity = { 5.0f, 5.0f };//プレイヤーのスピード
		player.isAlive = true;//生きているかのフラグ
		player.hp = 20;//体力
		player.attackDamage = 2;//プレイヤーの攻撃力
		player.invincibilityTime = 0;//プレイヤーの無敵時間
		player.isInvincibility = false;//無敵のフラグ
	}
#pragma endregion


	
#pragma region ボタンの変数
	//プレイヤーの攻撃ボタンの変数//
	Box attackButton;
	attackButton.pos = { 550.0f, 550.0f };
	attackButton.size = { 128.0f, 64.0f };
	int attackTimer = 0;
	int isAttackTimer = false;

	//チュートリアルを開始するためのボタンの変数//
	Box tutorialButton;
	tutorialButton.pos = { 600.0f, 450.0f };
	tutorialButton.size = { 256.0f, 128.0f };

	//ゲームを開始するための変数//
	Box startButton;
	startButton.pos = { 1000.0f, 450.0f };
	startButton.size = { 256.0f, 128.0f };

	//タイトルへ戻るためのボタン//
	Box titleButton;
	titleButton.pos = { 200.0f, 450.0f };
	titleButton.size = { 256.0f, 128.0f };
 #pragma endregion 

 #pragma region ボスの第一形態に使う変数

	//最初の雑魚的の変数
	 Enemy bossFirst;
	bossFirst.screenPos = { 600,50 };//mobの座標
	bossFirst.size = { 128.0f, 128.0f };//mobのサイズ
	bossFirst.hp = 20;//敵のhp
	bossFirst.isAlive = true;
	bossFirst.shootCoolTime = 0;
	bossFirst.isBulletCool = true;
	bossFirst.attackFrame = 0;
	bossFirst.attackPattern = 1;
	bossFirst.hitFrame = 0;
	bossFirst.isHit = false;

	//mobの攻撃に使う変数
	const int kBossBulletMax = 80;

	//各散弾の変数//

	EnemyAttack bossShotgunBullets[kBossBulletMax];
	for (int i = 0; i < kBossBulletMax; i++)
	{
		bossShotgunBullets[i].pos = { bossFirst.screenPos.x + (bossFirst.size.x / 2), bossFirst.screenPos.y + (bossFirst.size.y / 2) };
		bossShotgunBullets[i].size = { 16.0f, 16.0f };
		bossShotgunBullets[i].velocity = { 10.0f,10.0f };
		bossShotgunBullets[i].attackDamage = 2;
		bossShotgunBullets[i].isBulletShoot = false;
	}

	//上から降ってくる乱数弾の変数//
	EnemyAttack bossRandUpBullets[kBossBulletMax];
	for (int i = 0; i < kBossBulletMax; i++)
	{
		bossRandUpBullets[i].pos = { bossFirst.screenPos.x + (bossFirst.size.x / 2), bossFirst.screenPos.y + (bossFirst.size.y / 2) };
		bossRandUpBullets[i].size = { 16.0f, 16.0f };
		bossRandUpBullets[i].velocity = { 10.0f,10.0f };
		bossRandUpBullets[i].attackDamage = 2;
		bossRandUpBullets[i].isBulletShoot = false;
		bossRandUpBullets[i].frame = 0;
	}

	//上から降ってくる乱数弾の変数//
	EnemyAttack bossRandLeftRightBullets[kBossBulletMax];
	for (int i = 0; i < kBossBulletMax; i++)
	{
		bossRandLeftRightBullets[i].pos = { bossFirst.screenPos.x + (bossFirst.size.x / 2), bossFirst.screenPos.y + (bossFirst.size.y / 2) };
		bossRandLeftRightBullets[i].size = { 16.0f, 16.0f };
		bossRandLeftRightBullets[i].velocity = { 10.0f,10.0f };
		bossRandLeftRightBullets[i].attackDamage = 2;
		bossRandLeftRightBullets[i].isBulletShoot = false;
		bossRandLeftRightBullets[i].frame = 0;
	}

	//バウンズの変数//
	EnemyAttack bossBounceBullets[kBossBulletMax];
	for (int i = 0; i < kBossBulletMax; i++)
	{
		bossBounceBullets[i].pos = { bossFirst.screenPos.x + (bossFirst.size.x / 2), bossFirst.screenPos.y + (bossFirst.size.y / 2) };
		bossBounceBullets[i].size = { 16.0f, 16.0f };
		bossBounceBullets[i].velocity = { 10.0f,10.0f };
		bossBounceBullets[i].attackDamage = 2;
		bossBounceBullets[i].isBulletShoot = false;
		bossBounceBullets[i].frame = 0;
		bossBounceBullets[i].acceleration = { 16.0f, -16.0f };
		bossBounceBullets[i].e = 1.0f;
	}

	//移動場所を制限してから攻撃する攻撃の変数//

	EnemyAttack  bossExternaLlimitAttck[kBossBulletMax];
	for (int i = 0; i < 2; i++)
	{
		bossBounceBullets[i].pos = { bossFirst.screenPos.x + (bossFirst.size.x / 2), bossFirst.screenPos.y + (bossFirst.size.y / 2) };
		bossBounceBullets[i].size = { 480.0f, 720.0f };
		bossBounceBullets[i].velocity = { 10.0f,10.0f };
		bossBounceBullets[i].attackDamage = 2;
		bossBounceBullets[i].isBulletShoot = false;
		bossBounceBullets[i].frame = 0;
		
	}
	for (int i = 2; i < kBossBulletMax; i++)
	{
		bossBounceBullets[i].pos = { bossFirst.screenPos.x + (bossFirst.size.x / 2), bossFirst.screenPos.y + (bossFirst.size.y / 2) };
		bossBounceBullets[i].size = { 16.0f, 16.0f };
		bossBounceBullets[i].velocity = { 10.0f,10.0f };
		bossBounceBullets[i].attackDamage = 2;
		bossBounceBullets[i].isBulletShoot = false;
		bossBounceBullets[i].frame = 0;
	}

	float  theta = 120.0f;
	float thetaSpeed = 2.0f;

#pragma endregion
 #pragma region ポス第二形態に使う変数
	Object bossSecond;
	bossSecond.pos.x = 640.0f;
	bossSecond.pos.y = 50.0f;
	bossSecond.speed = 3.0f;
	bossSecond.width = 64.0f;
	bossSecond.height = 64.0f;
	bossSecond.radius = 16.0f;
	bossSecond.radius;
	bossSecond.isMove = false;
	bossSecond.isWait = true;
	bossSecond.moveCount = 480;//敵の
	bossSecond.waitCount = 60;//敵が大攻撃するまで待つフレームカウント
	bossSecond.attackCount = 480;//敵の大攻撃のフレームカウントする関数
	bossSecond.moveRight = 1;//青オレンジ攻撃の関数

	//棒:横移動
	bossSecond.attackPos[0].x = 0.0f;
	bossSecond.attackPos[0].y = 180.0f;
	bossSecond.attackPos[1].x = 1280.0f;
	bossSecond.attackPos[1].y = 360.0f;
	bossSecond.attackPos[2].x = 0.0f;
	bossSecond.attackPos[2].y = 540.0f;

	//棒:縦移動
	bossSecond.attackPos[3].x = 0.0f;
	bossSecond.attackPos[3].y = 180.0f;
	bossSecond.attackPos[4].x = 640.0f;
	bossSecond.attackPos[4].y = 720.0f;


	//エリアの左の壁
	bossSecond.attackPos[5].x = -640.0f;
	bossSecond.attackPos[5].y = 0.0f;


	//敵の大攻撃の初期化
	int enemyAttack[4] = {};
	enemyAttack[0] = false;
	enemyAttack[1] = false;
	enemyAttack[2] = false;
	enemyAttack[3] = false;

	//敵の移動パターンの初期化
	int enemyMove[4] = {};
	enemyMove[0] = false;
	enemyMove[1] = false;
	enemyMove[2] = false;
	enemyMove[3] = false;

	//randの初期化するやつ
	time_t currentTime = time(nullptr);  // time_t 型に変更
	srand(static_cast<unsigned int>(currentTime));
 #pragma endregion 

	







	//セレクトするための変数
	int select = 0;
	
#pragma region 画像読み込み

	//画像読み込み
	int playerDownImages = Novice::LoadTexture("./Resoucers/images/playerDown.png");//プレイヤーの下向き
	int playerUpimages = Novice::LoadTexture("./Resoucers/images/playerUp.png");//プレイヤーの上向き
	int playerLeftImages = Novice::LoadTexture("./Resoucers/images/playerLeft.png");//プレイヤーの左向き
	int playerRightImages = Novice::LoadTexture("./Resoucers/images/playerRight.png");//プレイヤーの右向き
	int boss1BackGroundImages = Novice::LoadTexture("./Resoucers/images/boss1BackGraund.png");//ボスの第一形態に使う背景
	int boss2BackGroundImages = Novice::LoadTexture("./Resoucers/images/boss2BackGraund.png");//ボスの第二形態に使う背景
	int attckButtonImages = Novice::LoadTexture("./Resoucers/images/attackButton.png");//攻撃に使うコマンド
	int enemyBulletImages = Novice::LoadTexture("./Resoucers/images/enemyBullet.png");//ボスの弾
	int gameOverTitleImages = Novice::LoadTexture("./Resoucers/images/GameOverThree.png");//ゲームオーバー画面
	int gameOverRestartImages = Novice::LoadTexture("./Resoucers/images/GameOverTwo.png");
	int gameOverContinuationImages = Novice::LoadTexture("./Resoucers/images/GameOverOne.png");
	int tyutoriaruButtonImages = Novice::LoadTexture("./Resoucers/images/tyutoriaru.png");//チュートリアルへ行くためのボタン
	int startButtonImages = Novice::LoadTexture("./Resoucers/images/start.png");//スタートするためのボタン
	int beamTexture = Novice::LoadTexture("./Resoucers/images/beam.png");//ビーム攻撃
	int dangerTexture = Novice::LoadTexture("./Resoucers/images/keikoku.png");//ビーム攻撃の警告
	int boss1Images = Novice::LoadTexture("./Resoucers/images/smilerTypebug.png");//ボス第一形態
	int boss2Images = Novice::LoadTexture("./Resoucers/images/boss2.png");//ボス第二形態
 #pragma endregion 



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
				scene = BOSSFIRSTFORM;
			}

			break;
		case BOSSFIRSTFORM:

#pragma region プレイヤーの移動処理
			//playerの移動処理

			playerMove(player, keys);
			if (keys[DIK_A])
			{
				vector = LEFT;
			}
			if (keys[DIK_D])
			{
				vector = RIGHT;
			}
			if (keys[DIK_W])
			{
				vector = UP;
			}
			if (keys[DIK_S])
			{
				vector = DOWN;
			}
#pragma endregion 
#pragma region スタート前のボタンの当たり判定
			if (!isStart)
			{
				
				//プレイヤーとタイトルボタンの当たり判定//

				if (IsHitDetection(player.pos.x, player.pos.y, player.size.x, player.size.y,
					titleButton.pos.x, titleButton.pos.y, titleButton.size.x, titleButton.size.y))
				{
					if (keys[DIK_SPACE])//スペースキーを押すと
					{
						scene = TITLE;//タイトルへ戻る
					}
				}

				//プレイヤーとチュートリアルボタンの当たり判定//

				if (IsHitDetection(player.pos.x, player.pos.y, player.size.x, player.size.y,
					tutorialButton.pos.x, tutorialButton.pos.y, tutorialButton.size.x, tutorialButton.size.y))
				{
					if (keys[DIK_SPACE])//スペースキーを押すと
					{
						isTutorial = true;//チュートリアルが始まる
					}
				}

				//プレイヤーとスタートボタンの当たり判定//

				if (IsHitDetection(player.pos.x, player.pos.y, player.size.x, player.size.y,
					startButton.pos.x, startButton.pos.y, startButton.size.x, startButton.size.y))
				{
					if (keys[DIK_SPACE])//スペースキーを押すと
					{
						isStart = true;//チュートリアルが始まる
					}
				}

			}
#pragma endregion


			//ゲームスタートのコマンドが押されるとゲームを開始する//
			if (isStart)
			{


				//攻撃パターンをランダムにするための処理//
				if (bossFirst.isAlive)
				{
					bossFirst.attackFrame++;
					if (bossFirst.attackFrame >= 280)
					{
						bossFirst.attackFrame = 0;
						bossFirst.attackPattern = int(rand() % 3 + 1);
					}
				}


#pragma region 第一形態のボスの攻撃処理と当たり判定
				//mobの各散弾//

					//当たり判定//

				for (int i = 0; i < kBossBulletMax; i++)
				{
					if (IsHitDetection(player.pos.x, player.pos.y, player.size.x, player.size.y,
						bossShotgunBullets[i].pos.x, bossShotgunBullets[i].pos.y, bossShotgunBullets[i].size.x, bossShotgunBullets[i].size.y))
					{
						if (!player.isInvincibility)
						{
							player.isInvincibility = true;
							player.hp = player.hp - bossShotgunBullets[i].attackDamage;
						}

					}
				}
				//角度を動かす処理//
				theta += thetaSpeed;
				if (theta > 160.0f || theta < 80.0f)
				{
					thetaSpeed *= -1.0f;
				}

				shotgunBullets(bossShotgunBullets, bossFirst, kBossBulletMax, theta);

				//上から降ってくる乱数弾//

											//当たり判定//
				for (int i = 0; i < kBossBulletMax; i++)
				{
					if (IsHitDetection(player.pos.x, player.pos.y, player.size.x, player.size.y,
						bossRandUpBullets[i].pos.x, bossRandUpBullets[i].pos.y, bossRandUpBullets[i].size.x, bossRandUpBullets[i].size.y))
					{
						if (!player.isInvincibility)
						{
							player.isInvincibility = true;
							player.hp = player.hp - bossRandUpBullets[i].attackDamage;
						}

					}
				}
				randUpBullets(bossRandUpBullets, bossFirst, kBossBulletMax);

				//左右から攻撃する乱数弾//

										//当たり判定//
				for (int i = 0; i < kBossBulletMax; i++)
				{
					if (IsHitDetection(player.pos.x, player.pos.y, player.size.x, player.size.y,
						bossRandLeftRightBullets[i].pos.x, bossRandLeftRightBullets[i].pos.y, bossRandLeftRightBullets[i].size.x, bossRandLeftRightBullets[i].size.y))
					{
						if (!player.isInvincibility)
						{
							player.isInvincibility = true;
							player.hp = player.hp - bossRandLeftRightBullets[i].attackDamage;
						}

					}
				}
				randLeftRightBullets(bossRandLeftRightBullets, bossFirst, kBossBulletMax);
#pragma endregion 



#pragma region プレイヤーの移動制限 
				//プレイヤーの移動制限
				if (player.pos.x + player.size.x >= windowsWidth) {
					player.pos.x = windowsWidth - player.size.x;
				}

				if (player.pos.x <= 0) {
					player.pos.x = 0;
				}

				if (player.pos.y + player.size.y >= windowsHeight) {
					player.pos.y = windowsHeight - player.size.y;
				}

				if (player.pos.y <= 250.0f) {
					player.pos.y = 250.0f;
				}
 #pragma endregion

				//攻撃するとフラグがtrueになりしばらく攻撃ができない//

				if (isAttackTimer)
				{
					attackTimer++;
				}

				//タイマーが300になるとコマンドの描画を再度出現させる//

				if (attackTimer > 300)
				{
					isAttackTimer = false;
					attackTimer = 0;
				}

				//プレイヤーとコマンドの当たり判定//

				if (IsHitDetection(player.pos.x, player.pos.y, player.size.x, player.size.y,
					attackButton.pos.x, attackButton.pos.y, attackButton.size.x, attackButton.size.y))
				{
					if (keys[DIK_SPACE] && !isAttackTimer)
					{
						isAttackTimer = true;
						bossFirst.hp = bossFirst.hp - player.attackDamage;
						bossFirst.isHit = true;
					}
				}



				//ダメージ受けたらtrueになって一定時間無敵になる//

				if (player.isInvincibility)
				{
					player.invincibilityTime++;
				}
				if (player.invincibilityTime >= 30)
				{
					player.invincibilityTime = 0;
					player.isInvincibility = false;
				}

				//敵にダメージ与えた時の描画のための処理//
				if (bossFirst.isHit)
				{
					bossFirst.hitFrame++;
				}
				if (bossFirst.hitFrame >= 30)
				{
					bossFirst.hitFrame = 0;
					bossFirst.isHit = false;
				}

				////playerのhpが０になったらGAMEOVER
				//if (player.hp <= 0)
				//{
				//	isStart = false;
				//	scene = GAMEOVER;
				//}

				//mobのHPが0になったらboss1が死亡する
				if (bossFirst.hp <= 0)
				{
					bossFirst.isAlive = false;
					scene = BOSSSECONDFORM;
				}

			}

			break;
		case BOSSSECONDFORM:
			//背景描画//

			Novice::DrawSprite(0, 0, boss2BackGroundImages, 1.0f, 1.0f, 0.0f, WHITE);

#pragma region プレイヤーの移動処理
			//playerの移動処理

			playerMove(player, keys);
			if (keys[DIK_A])
			{
				vector = LEFT;
			}
			if (keys[DIK_D])
			{
				vector = RIGHT;
			}
			if (keys[DIK_W])
			{
				vector = UP;
			}
			if (keys[DIK_S])
			{
				vector = DOWN;
			}
#pragma endregion 
#pragma region プレイヤーの移動制限 
			//プレイヤーの移動制限
			if (player.pos.x + player.size.x >= windowsWidth) {
				player.pos.x = windowsWidth - player.size.x;
			}

			if (player.pos.x <= 0) {
				player.pos.x = 0;
			}

			if (player.pos.y + player.size.y >= windowsHeight) {
				player.pos.y = windowsHeight - player.size.y;
			}

			if (player.pos.y <= 250.0f) {
				player.pos.y = 250.0f;
			}
#pragma endregion
			//=============================================
	//ボスが動くときと止まるときを切り替えるタイマー
	//=============================================
			if ( bossSecond.isMove) {
				 bossSecond.moveCount -= 1;
			}
			if ( bossSecond.isWait) {
				 bossSecond.waitCount -= 1;
			}
			if ( bossSecond.waitCount <= 0) {
				 bossSecond.isWait = false;
				 bossSecond.isMove = true;
			} else if ( bossSecond.attackCount <= 1) {
				 bossSecond.isWait = true;
				 bossSecond.isMove = false;
			}
			if ( bossSecond.moveCount == 0) {
				 bossSecond.moveCount = 480;
			} else if ( bossSecond.waitCount == 0) {
				 bossSecond.waitCount = 60;//実験中のため60
			}

			//=============================================
			//ボスのギミック攻撃パターンの抽選
			//=============================================

			if ( bossSecond.waitCount == 1) {
				for (int i = 1; i < 4; i++) {

					 bossSecond.attackRandum = rand() % 4 + 1;

					if ( bossSecond.attackRandum == 1) {
						 bossSecond.moveCount = 480;//ここに敵の移動持続時間を入れる
						 bossSecond.attackCount = 480;//ここに敵の攻撃持続時間を入れる
						if ( bossSecond.attackCount >= 1) {
							enemyAttack[0] = true;
							enemyAttack[1] = false;
							enemyAttack[2] = false;
							enemyAttack[3] = false;
						}
					}
					if ( bossSecond.attackRandum == 2) {
						 bossSecond.moveCount = 510;//ここに敵の移動持続時間を入れる
						 bossSecond.attackCount = 510;//ここに敵の攻撃持続時間を入れる
						if ( bossSecond.attackCount >= 1) {
							enemyAttack[0] = false;
							enemyAttack[1] = true;
							enemyAttack[2] = false;
							enemyAttack[3] = false;
						}
					}
					if ( bossSecond.attackRandum == 3) {
						 bossSecond.moveCount = 1000;//ここに敵の移動持続時間を入れる
						 bossSecond.attackCount = 1000;//ここに敵の攻撃持続時間を入れる
						if ( bossSecond.attackCount >= 1) {
							enemyAttack[0] = false;
							enemyAttack[1] = false;
							enemyAttack[2] = true;
							enemyAttack[3] = false;
						}
					}
					if ( bossSecond.attackRandum == 4) {
						 bossSecond.moveCount = 210;//ここに敵の移動持続時間を入れる
						 bossSecond.attackCount = 210;//ここに敵の攻撃持続時間を入れる
						if ( bossSecond.attackCount >= 1) {
							enemyAttack[0] = false;
							enemyAttack[1] = false;
							enemyAttack[2] = false;
							enemyAttack[3] = true;
						}
					}
				}
			}
			//=============================================
			//ボスの行動パターンの抽選
			//=============================================
			if ( bossSecond.waitCount == 1) {
				for (int j = 1; j < 4; j++) {
					 bossSecond.moveRandum = rand() % 4 + 1;

					if ( bossSecond.moveRandum == 1) {
						if ( bossSecond.moveCount <= 479) {
							enemyMove[0] = true;
							enemyMove[1] = false;
							enemyMove[2] = false;
							enemyMove[3] = false;
						}
					}
					if ( bossSecond.moveRandum == 2) {
						if ( bossSecond.moveCount <= 479) {
							enemyMove[0] = false;
							enemyMove[1] = true;
							enemyMove[2] = false;
							enemyMove[3] = false;
						}
					}
					if ( bossSecond.moveRandum == 3) {
						if ( bossSecond.moveCount <= 479) {
							enemyMove[0] = false;
							enemyMove[1] = false;
							enemyMove[2] = true;
							enemyMove[3] = false;
						}
					}
					if ( bossSecond.moveRandum == 4) {
						if ( bossSecond.moveCount <= 479) {
							enemyMove[0] = false;
							enemyMove[1] = false;
							enemyMove[2] = false;
							enemyMove[3] = true;
						}
					}

				}
			}

			//=============================================
			//ボスの大攻撃の詳細
			//=============================================
			if (enemyAttack[0]) {

				///範囲ビーム攻撃*横320縦540
				 bossSecond.attackCount -= 1;
				if ( bossSecond.attackCount <= 0) {
					enemyAttack[0] = false;

				}
				if ( bossSecond.attackCount <= 480 &&  bossSecond.attackCount > 420) {
					Novice::DrawSprite(0, 180, dangerTexture, 1, 1, 0.0f, 0xffffffff);
				}
				if ( bossSecond.attackCount <= 420 &&  bossSecond.attackCount > 360) {
					Novice::DrawSprite(320, 180, dangerTexture, 1, 1, 0.0f, 0xffffffff);
				}
				if ( bossSecond.attackCount <= 360 &&  bossSecond.attackCount > 300) {
					Novice::DrawSprite(960, 180, dangerTexture, 1, 1, 0.0f, 0xffffffff);
				}
				if ( bossSecond.attackCount <= 300 &&  bossSecond.attackCount > 240) {
					Novice::DrawSprite(640, 180, dangerTexture, 1, 1, 0.0f, 0xffffffff);
				}

				if ( bossSecond.attackCount <= 240 &&  bossSecond.attackCount > 180) {
					Novice::DrawSprite(0, 180, beamTexture, 1, 1, 0.0f, 0xffffffff);
				}
				if ( bossSecond.attackCount <= 180 &&  bossSecond.attackCount > 120) {
					Novice::DrawSprite(320, 180, beamTexture, 1, 1, 0.0f, 0xffffffff);
				}
				if ( bossSecond.attackCount <= 120 &&  bossSecond.attackCount > 60) {
					Novice::DrawSprite(960, 180, beamTexture, 1, 1, 0.0f, 0xffffffff);
				}
				if ( bossSecond.attackCount <= 60 &&  bossSecond.attackCount > 0) {
					Novice::DrawSprite(640, 180, beamTexture, 1, 1, 0.0f, 0xffffffff);
				}

			}
			if (enemyAttack[1]) {

				///よこから棒が移動してくる
				 bossSecond.attackCount -= 1;
				if ( bossSecond.attackCount <= 0) {
					enemyAttack[1] = false;

				}



				if ( bossSecond.attackCount > 0) {
					if ( bossSecond.attackPos[0].x >= 1275.0f) {
						 bossSecond.moveRight = false;

					} else if ( bossSecond.attackPos[0].x == 0.0f) {
						 bossSecond.moveRight = true;

					}

					if ( bossSecond.moveRight) {
						 bossSecond.attackPos[0].x += 5.0f;
						 bossSecond.attackPos[1].x -= 5.0f;
						 bossSecond.attackPos[2].x += 5.0f;
						 bossSecond.attackPos[3].y += 2.5f;
						 bossSecond.attackPos[4].y -= 2.5f;


					} else if (! bossSecond.moveRight) {
						 bossSecond.attackPos[0].x -= 5.0f;
						 bossSecond.attackPos[1].x += 5.0f;
						 bossSecond.attackPos[2].x -= 5.0f;
						 bossSecond.attackPos[3].y -= 2.5f;
						 bossSecond.attackPos[4].y += 2.5f;

					}

					Novice::DrawBox(static_cast<int>( bossSecond.attackPos[0].x), static_cast<int>( bossSecond.attackPos[0].y), 5, 180, 0.0f, 0xffffffff, kFillModeSolid);
					Novice::DrawBox(static_cast<int>( bossSecond.attackPos[1].x), static_cast<int>( bossSecond.attackPos[1].y), 5, 180, 0.0f, 0xffffffff, kFillModeSolid);
					Novice::DrawBox(static_cast<int>( bossSecond.attackPos[2].x), static_cast<int>( bossSecond.attackPos[2].y), 5, 180, 0.0f, 0xffffffff, kFillModeSolid);
					Novice::DrawBox(static_cast<int>( bossSecond.attackPos[3].x), static_cast<int>( bossSecond.attackPos[3].y), 640, 5, 0.0f, 0xffffffff, kFillModeSolid);
					Novice::DrawBox(static_cast<int>( bossSecond.attackPos[4].x), static_cast<int>( bossSecond.attackPos[4].y), 640, 5, 0.0f, 0xffffffff, kFillModeSolid);
				}


			}
			if (enemyAttack[2]) {

				///画面が制限された中での攻撃(今のところ壁だけ)
				 bossSecond.attackCount -= 1;
				if ( bossSecond.attackCount <= 0) {
					enemyAttack[2] = false;

				}
				if ( bossSecond.attackCount >= 900) {
					 bossSecond.attackPos[5].x += 6.4f;
				}
				if ( bossSecond.attackCount <= 100) {
					 bossSecond.attackPos[5].x -= 6.4f;
				}

				Novice::DrawBox(static_cast<int>( bossSecond.attackPos[5].x), static_cast<int>( bossSecond.attackPos[5].y), 640, 720, 0.0f, 0xffffffff, kFillModeSolid);

			}
			if (enemyAttack[3]) {

				///青オレンジ攻撃
				 bossSecond.attackCount -= 1;
				if ( bossSecond.attackCount <= 0) {
					enemyAttack[3] = false;
					 bossSecond.moveRight = 1;
				}

				if ( bossSecond.attackCount <= 210 &&  bossSecond.attackCount > 180) {
					Novice::DrawBox(0, 180, 1280, 720, 0.0f, 0x4169e1ff, kFillModeSolid);
				};
				if ( bossSecond.attackCount <= 180 &&  bossSecond.attackCount > 150) {
					Novice::DrawBox(0, 180, 1280, 720, 0.0f, 0xff4500ff, kFillModeSolid);
				};
				if ( bossSecond.attackCount <= 150 &&  bossSecond.attackCount > 120) {
					Novice::DrawBox(0, 180, 1280, 720, 0.0f, 0x4169e1ff, kFillModeSolid);
				};

				if ( bossSecond.attackCount <= 90 &&  bossSecond.attackCount > 60) {
					 bossSecond.moveRight = 2;
					Novice::DrawBox(0, 180, 1280, 720, 0.0f, 0x4169e1ff, kFillModeSolid);
				};
				if ( bossSecond.attackCount <= 60 &&  bossSecond.attackCount > 30) {
					 bossSecond.moveRight = 3;
					Novice::DrawBox(0, 180, 1280, 720, 0.0f, 0xff4500ff, kFillModeSolid);

				};
				if ( bossSecond.attackCount <= 30 &&  bossSecond.attackCount > 0) {
					 bossSecond.moveRight = 2;
					Novice::DrawBox(0, 180, 1280, 720, 0.0f, 0x4169e1ff, kFillModeSolid);
				};

				// 移動キーが押されているかどうかをチェック
				bool isAnyKeyPressed = (keys[DIK_S] != 0 || keys[DIK_W] != 0 || keys[DIK_A] != 0 || keys[DIK_D] != 0);

				if ( bossSecond.moveRight == 2) {
					if (isAnyKeyPressed) {
						// 何らかの移動キーが押された場合
						Novice::DrawEllipse(900, 400, 200, 200, 0.0f, 0xffff1212, kFillModeSolid);//debug

					}
				} else if ( bossSecond.moveRight == 3) {
					if (!isAnyKeyPressed) {
						// 何も移動キーが押されてない場合
						Novice::DrawEllipse(900, 400, 200, 200, 0.0f, 0xffff1212, kFillModeSolid);//debug

					}
				}

			};

			//=============================================
			//ボスの移動の詳細(なくてもいい)
			//=============================================

			if (enemyMove[0]) {
				//移動の動作名

			}
			if (enemyMove[1]) {
				//移動の動作名

			}
			if (enemyMove[2]) {
				//移動の動作名

			}
			if (enemyMove[3]) {
				//移動の動作名

			}

			break;
		case GAMECLEAR:

			//spaceキーを押すとタイトルへ戻る処理//
			if (keys[DIK_SPACE])
			{
				scene = TITLE;
			}

			break;
		case GAMEOVER:
			//リスタートかタイトルへ戻るかを選ぶ処理//

			if (keys[DIK_W] && preKeys[DIK_W] == 0)
			{
				select -= 1;
			}
			if (keys[DIK_S] && preKeys[DIK_S] == 0)
			{
				select += 1;
			}
			if (select > 2)
			{
				select = 2;
			}
			if (select < 0)
			{
				select = 0;
			}

			//コンテニュー//

			if (select == 0)
			{
				if (keys[DIK_SPACE])
				{
					scene = BOSSFIRSTFORM;
					//初期化//
					player.hp = 20;
					isStart = true;
					bossFirst.isAlive = true;
					
				}
			}
			//完全リスタート//
			else if (select == 1)
			{
				if (keys[DIK_SPACE])
				{
					scene = BOSSFIRSTFORM;
					//初期化//
					player.hp = 20;
					bossFirst.hp = 20;
					isStart = true;
				}

			}
			//タイトルへ戻る//
			else if (select == 2)
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
		case BOSSFIRSTFORM:

			//背景描画//

			Novice::DrawSprite(0, 0, boss1BackGroundImages, 1.0f, 1.0f, 0.0f, WHITE);



#pragma region スタート前に使うボタンの描画
			//チュートリアルボタンが押されていないとき//
			if (!isStart) {
				
					Novice::DrawSprite(int(titleButton.pos.x), int(titleButton.pos.y),
						tyutoriaruButtonImages, 1.0f, 1.0f, 0.0f, WHITE);
				
				if (!isTutorial)
				{
					Novice::DrawSprite(int(tutorialButton.pos.x), int(tutorialButton.pos.y),
					tyutoriaruButtonImages,1.0f, 1.0f, 0.0f, WHITE);
				}



				//スタートボタンが押されていないとき//

				Novice::DrawSprite(int(startButton.pos.x), int(startButton.pos.y),
					startButtonImages,1.0f, 1.0f, 0.0f, WHITE);
			}
#pragma endregion

			//スタートボタンが押されたら//
			if (isStart)
			{


				//プレイヤーの攻撃コマンド描画//

				if (!isAttackTimer)
				{
					Novice::DrawSprite(int(attackButton.pos.x), int(attackButton.pos.y), attckButtonImages,
						1.0f, 1.0f, 0.0f, WHITE);
				}
 #pragma region 第一形態のボスの攻撃に使う弾の描画 
				//弾の拡散弾の描画//

				for (int i = 0; i < kBossBulletMax; i++)
				{
					if (bossShotgunBullets[i].isBulletShoot)
					{
						Novice::DrawSprite(int(bossShotgunBullets[i].pos.x), int(bossShotgunBullets[i].pos.y),
							enemyBulletImages, 1.0f, 1.0f, 0.0f, WHITE);
					}
					//上から降ってくる乱数弾の描画//


					if (bossRandUpBullets[i].isBulletShoot)
					{
						Novice::DrawSprite(int(bossRandUpBullets[i].pos.x), int(bossRandUpBullets[i].pos.y),
							enemyBulletImages, 1.0f, 1.0f, 0.0f, WHITE);
					}
					//左右から出てくる乱数弾

					if (bossRandLeftRightBullets[i].isBulletShoot)
					{
						Novice::DrawSprite(int(bossRandLeftRightBullets[i].pos.x), int(bossRandLeftRightBullets[i].pos.y),
							enemyBulletImages, 1.0f, 1.0f, 0.0f, WHITE);
					}


				}
#pragma endregion 


				//ボスの第一形態の敵の描画//

				if (bossFirst.isAlive && bossFirst.hitFrame % 4 <= 1)
				{
					Novice::DrawSprite(int(bossFirst.screenPos.x), int(bossFirst.screenPos.y), boss1Images, 1.0f, 1.0f, 0.0f, WHITE);
				}
			}
			//プレイヤーの描画//
			if (player.invincibilityTime % 4 <= 1) {
				//下向き
				if (player.isAlive && vector == DOWN)
				{
					Novice::DrawSprite(int(player.pos.x), int(player.pos.y), playerDownImages, 1.0f, 1.0f, 0.0f, WHITE);
				}

				//上向き
				if (player.isAlive && vector == UP)
				{
					Novice::DrawSprite(int(player.pos.x), int(player.pos.y), playerUpimages, 1.0f, 1.0f, 0.0f, WHITE);
				}
				//左向き
				if (player.isAlive && vector == LEFT)
				{
					Novice::DrawSprite(int(player.pos.x), int(player.pos.y), playerLeftImages, 1.0f, 1.0f, 0.0f, WHITE);
				}

				//右向き
				if (player.isAlive && vector == RIGHT)
				{
					Novice::DrawSprite(int(player.pos.x), int(player.pos.y), playerRightImages, 1.0f, 1.0f, 0.0f, WHITE);
				}
			}

			//体力の確認のために描画//

			Novice::ScreenPrintf(0, 0, "playerHP%d", player.hp);

			Novice::ScreenPrintf(0, 50, "mobHP%d", bossFirst.hp);
			break;
		case BOSSSECONDFORM:
		
			//ボスの第二形態の敵の描画//

		
				Novice::DrawSprite(int(bossSecond.pos.x), int(bossSecond.pos.y), boss2Images, 1.0f, 1.0f, 0.0f, WHITE);

			
			//プレイヤーの描画//
			if (player.invincibilityTime % 4 <= 1) {
				//下向き
				if (player.isAlive && vector == DOWN)
				{
					Novice::DrawSprite(int(player.pos.x), int(player.pos.y), playerDownImages, 1.0f, 1.0f, 0.0f, WHITE);
				}

				//上向き
				if (player.isAlive && vector == UP)
				{
					Novice::DrawSprite(int(player.pos.x), int(player.pos.y), playerUpimages, 1.0f, 1.0f, 0.0f, WHITE);
				}
				//左向き
				if (player.isAlive && vector == LEFT)
				{
					Novice::DrawSprite(int(player.pos.x), int(player.pos.y), playerLeftImages, 1.0f, 1.0f, 0.0f, WHITE);
				}

				//右向き
				if (player.isAlive && vector == RIGHT)
				{
					Novice::DrawSprite(int(player.pos.x), int(player.pos.y), playerRightImages, 1.0f, 1.0f, 0.0f, WHITE);
				}
			}


			break;
		case GAMECLEAR:
			break;
		case GAMEOVER:
			if (select == 0) {

				Novice::DrawSprite(0, 0, gameOverContinuationImages, 1.0f, 1.0f, 0.0f, WHITE);
			}
			if (select == 1) {

				Novice::DrawSprite(0, 0, gameOverRestartImages, 1.0f, 1.0f, 0.0f, WHITE);
			}
			if (select == 2) {

				Novice::DrawSprite(0, 0, gameOverTitleImages, 1.0f, 1.0f, 0.0f, WHITE);
			}
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
