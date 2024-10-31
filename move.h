#include <Novice.h>
void playerMove(Box& player, char keys[]) {
	if (keys[DIK_A])
	{
		player.pos.x -= player.speed;
	}
	if (keys[DIK_D])
	{
		player.pos.x += player.speed;
	}
	if (keys[DIK_W])
	{
		player.pos.y -= player.speed;
	}
	if (keys[DIK_S])
	{
		player.pos.y += player.speed;
	}
}