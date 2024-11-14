#include <Novice.h>
#include "struct.h"
int vector = UP;
void playerMove(Box& player, char keys[]) {
	if (keys[DIK_A])
	{
		vector = LEFT;
		player.pos.x -= player.velocity.x;
	}
	if (keys[DIK_D])
	{
		vector = RIGHT;
		player.pos.x += player.velocity.x;
	}
	if (keys[DIK_W])
	{
		vector = UP;
		player.pos.y -= player.velocity.y;
	}
	if (keys[DIK_S])
	{
		vector = DOWN;
		player.pos.y += player.velocity.y;
	}
}