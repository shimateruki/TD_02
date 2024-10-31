#pragma once
/*---------
＊構造体
---------*/
/*2次元ベクトル*/
typedef struct Vecter2 {
	float x;
	float y;
} Vector2;
/*プレイヤー*/
typedef struct Player {
	Vecter2 screenPos{};
	Vecter2 size{};
	Vecter2 width{};
	Vecter2 velocity{};
	int isAlive{};
	int handle{};
} Box;