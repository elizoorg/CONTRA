#include "Bullet.h"
#include <SDL_image.h>

Bullet::Bullet()
{

}



Bullet::~Bullet()
{
	SDL_DestroyTexture(text1);
}

void Bullet::setTexture(SDL_Renderer* render)
{
	SDL_Surface* test1 = IMG_Load("bull.png");
	if (!test1) {
		printf("Unable to load image %s! SDL_image Error: %s\n", "bull.png", IMG_GetError());
	}
	text1 = SDL_CreateTextureFromSurface(render, test1);
	if (!text1) {
		printf("Unable to create texture from %s! SDL Error: %s\n", "bull.png", SDL_GetError());
	}
	SDL_FreeSurface(test1);
}

void Bullet::setPos(vec2i pos)
{
	posit = pos;
}

void Bullet::setVel(vec2f vel)
{
	velos = vel;
}



void Bullet::Move()
{
	double an = angle * 3.14 / 180;
	switch (angle) {
	case 0:dx = 3; dy = 0; break;
	case 180:dx = -3; dy = 0; break;
	case 270: dx = 0; dy = -3; break;
	case 45:dx = 3; dy = 2; break;
	case 135: dx = -3; dy = 2; break;
	case 225:dx = -3; dy = -2; break;
	case -45:dx = 3; dy = -2; break;

	}
	posit.x+= dx*velocity;
	posit.y+= dy*velocity;
	pos.x = posit.x;
	pos.y = posit.y;
}

void Bullet::Draw(SDL_Renderer* render, vec2i camerax)
{
	pos.x -=camerax.x;
	pos.y -=camerax.y;
	pos.w = 20;
	pos.h = 20;
	//cout << pos.x <<" " <<  pos.y << " " << pos.w << " "<< pos.h<< endl;
	SDL_RenderCopy(render, text1,0,&pos);
}
