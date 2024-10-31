#include <Novice.h>
enum Vector
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};
int vector = UP;
void playerMove(Box& player, char keys[]) {
	if (keys[DIK_A])
	{
		vector = LEFT;
		player.screenPos.x -= player.velocity.x;
	}
	if (keys[DIK_D])
	{
		vector = RIGHT;
		player.screenPos.x += player.velocity.x;
	}
	if (keys[DIK_W])
	{
		vector = UP;
		player.screenPos.y -= player.velocity.y;
	}
	if (keys[DIK_S])
	{
		vector = DOWN;
		player.screenPos.y += player.velocity.y;
	}
}