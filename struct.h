#pragma once
/*---------
���\����
---------*/
/*2�����x�N�g��*/
typedef struct Vecter2 {
	float x;
	float y;
} Vector2;
/*�v���C���[*/
typedef struct Player {
	Vecter2 screenPos{};
	Vecter2 size{};
	Vecter2 width{};
	Vecter2 velocity{};
	int isAlive{};
	int handle{};
} Box;