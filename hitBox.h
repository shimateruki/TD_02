#pragma once
/*
ax �Q�Ƃ�������`1�̍�����WX
ay �Q�Ƃ�������`1�̍�����WY
aWidth_x �Q�Ƃ�������`1�̉���
aWidth_y �Q�Ƃ�������`1�̏c��
ax �Q�Ƃ�������`2�̍�����WX
ay �Q�Ƃ�������`2�̍�����WY
bWidth_x �Q�Ƃ�������`2�̉���
bWidth_y �Q�Ƃ�������`2�̏c��
*/
int IsHitDetection(float playerPosX, float playerPosY, float playerWidthX, float playerWidthY, float bulletPosX, float bulletPosY, float bulletWidthX, float bulletWidthY);

/*
a �Q�Ƃ��������W
b ��ʏ��0�ƂȂ�ʒu
*/
int WorldCoordinate(int a, int b);
