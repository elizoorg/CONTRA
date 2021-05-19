#include "Alien.h"

Alien::Alien()
{
}

Alien::~Alien()
{
}

void Alien::Draw(SDL_Renderer* render, vec2i camerapos)
{
	clipRect.x = worldpos.x - camerapos.x;
	clipRect.y = worldpos.y - camerapos.y;
	if(speed>0)
	SDL_RenderCopy(render, texture, &sourceRect, &clipRect);
	else SDL_RenderCopyEx(render, texture, &sourceRect, &clipRect,0,0,SDL_FLIP_HORIZONTAL);
}

void Alien::setTexture(SDL_Renderer* render, string str)
{
	
}
