#pragma once
#include "Vector.h"
#include <SDL_image.h>
#include <SDL.h>
class Coins
{
public:
	Coins();
	~Coins();
	void Init(SDL_Renderer* render);
	void Update(vec2i camerapos);
	void Draw(SDL_Renderer* render);
	void SetPos(vec2i pos) { worldpos.x = pos.x; worldpos.y = pos.y; }
	SDL_Rect getRect(){ return SDL_Rect{ worldpos.x,worldpos.y,64,64 }; }
private:
	vec2i worldpos;
	int frameCounter = 0;
	SDL_Rect sourceRect = { 0,0,84,84 };
	SDL_Rect clipRect = { 0,0,64,64 };
	SDL_Texture* texture;
	SDL_Surface* surf;
};

