int IsHitDetection(float playerPosX, float playerPosY, float playerWidthX, float playerWidthY, float bulletPosX, float bulletPosY, float bulletWidthX, float bulletWidthY) {
	float playerx1 = playerPosX;
	float playery1 = playerPosY;
	float playerx2 = playerPosX + playerWidthX;
	float playery2 = playerPosY + playerWidthY;
	float bulletx1 = bulletPosX;
	float bullety1 = bulletPosY;
	float bulletx2 = bulletPosX + bulletWidthX;
	float bullety2 = bulletPosY + bulletWidthY;
	if (bulletx1 < playerx2 && playerx1 < bulletx2)
	{
		if (bullety1 < playery2 && playery1 < bullety2)
		{
			return true;
		}
	}
	return false;
}

int WorldCoordinate(int a, int b) {
	return a * -1 + b;
}