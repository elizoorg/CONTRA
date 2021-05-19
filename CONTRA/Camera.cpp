#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update(vec2i playerPos)
{
	worldpos.x = playerPos.x -600;
	worldpos.y = playerPos.y - 450;
	/*if (playerPos.x > worldpos.x + 540) worldpos.x += 5;
	if (playerPos.x < worldpos.x) worldpos -= 5;
	cout <<"Camera: " << worldpos.y<< " " << playerPos.y << " " << playerPos.y-worldpos.y <<endl;
	if (playerPos.y - worldpos.y > 450  ) worldpos.y += playerPos.y -450;
	if (worldpos.x < 0) worldpos.x += 5;*/
}