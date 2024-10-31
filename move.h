#include <Novice.h>
void playerMove(Box& player, char keys[]) {
	if (keys[DIK_A])
	{
		player.screenPos.x -= player.velocity.x;
	}
	if (keys[DIK_D])
	{
		player.screenPos.x += player.velocity.x;
	}
	if (keys[DIK_W])
	{
		player.screenPos.y -= player.velocity.y;
	}
	if (keys[DIK_S])
	{
		player.screenPos.y += player.velocity.y;
	}
}