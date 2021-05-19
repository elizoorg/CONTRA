#pragma once
#include "vector.h"
#include <SDL.h>

#define velocity 7 ;
class Bullet
{
public:
	Bullet();
	~Bullet();
	void setTexture(SDL_Renderer* render);
	void setPos(vec2i pos);
	void setVel(vec2f vel);
	void setAngle(int ang) { angle = ang; }
	vec2i getPos() { return posit; }
	SDL_Rect getRect(){ return SDL_Rect{ posit.x,posit.y,20,20 }; };
	void Move();
	void Draw(SDL_Renderer* render, vec2i camerax);
private:	
	vec2i posit;
	int coll;
	int angle;
	int dx, dy;
	vec2f velos;
	SDL_Rect pos;
	SDL_Texture* text1;
};

