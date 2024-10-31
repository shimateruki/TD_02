#pragma once
/*
ax 参照したい矩形1の左上座標X
ay 参照したい矩形1の左上座標Y
aWidth_x 参照したい矩形1の横幅
aWidth_y 参照したい矩形1の縦幅
ax 参照したい矩形2の左上座標X
ay 参照したい矩形2の左上座標Y
bWidth_x 参照したい矩形2の横幅
bWidth_y 参照したい矩形2の縦幅
*/
int IsHitDetection(float playerPosX, float playerPosY, float playerWidthX, float playerWidthY, float bulletPosX, float bulletPosY, float bulletWidthX, float bulletWidthY);

/*
a 参照したい座標
b 画面上の0となる位置
*/
int WorldCoordinate(int a, int b);
