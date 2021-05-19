#pragma once
#include "Vector.h"
class Camera
{
public:
	Camera();
	~Camera();
	vec2i getPos() { return worldpos; }
	int getWorldPosX() { return worldpos.x;}
	int getWorldPosY(){return worldpos.y;}
	void Update(vec2i playerPos);
private:
	vec2i worldpos{ 0,0 };
};

