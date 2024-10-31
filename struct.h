struct Vector2 {
	float x;
	float y;
};

typedef struct {
	Vector2 pos;
	float speed;
	Vector2 size;
}Player;
typedef struct
{
	Vector2 pos;
	float speed;
	float radius;
	int isBulletShot;
}Bullet;