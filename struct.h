
/*2次元ベクトル*/
typedef struct Vecter2 {
	float x;
	float y;
} Vector2;

//シーン

enum Scene
{
	TITLE,
	BOSSFIRSTFORM,
	BOSSSECONDFORM,
	GAMECLEAR,
	GAMEOVER,
};

//方向
enum Vector
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};
/*プレイヤー*/
typedef struct Player {
	Vecter2 pos{};
	Vecter2 size{};
	Vecter2 width{};
	Vecter2 velocity{};
	int hp{};
	int isAlive{};
	int handle{};
	int attackDamage{};
	int invincibilityTime;
	int isInvincibility;

} Box;
typedef struct Enemy
{
	Vecter2 screenPos{};
	Vecter2 size{};
	Vecter2 width{};
	Vecter2 velocity{};
	int hp{};
	int isAlive{};
	int shootCoolTime{};
	int isBulletCool{};
	int attackFrame{};
	int attackPattern{};
	int frame{};
	int hitFrame{};
	int isHit;
}Enemy;

typedef struct EnemyAttack {
	Vecter2 pos{};
	Vecter2 size{};
	Vector2 velocity{};
	int attackDamage{};
	int isBulletShoot;
	int isHoming{};
	int frame{};
	Vector2 acceleration{};
	float e{};
	int isPredictionLine{};
	
}EnemyAttack;

struct Object
{
	Vector2 pos;
	Vector2 attackPos[6];
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftBottom;
	Vector2 rightBottom;
	float speed;
	float width;
	float height;
	float radius;
	int moveRandum;
	int attackRandum;
	int isMove;
	int isWait;
	int moveCount;
	int waitCount;
	int attackCount;
	int moveRight;
};
