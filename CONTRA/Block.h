#pragma once
#include <SDL_rect.h>
#include <SDL.h>
#include <iostream>
#include "Vector.h"
using namespace std;
class Block
{
public:
	Block();
	~Block();
	Block(int x, int y, int id);
	void set(int x, int y, int id);
	SDL_Rect getRect();
	void Render(SDL_Renderer* render, SDL_Texture* blocks,vec2i camerax);
private:
	SDL_Rect border{ 0,0,32,32 };
	SDL_Rect source{ 32,32,16,16 };
	SDL_Rect clipRect{ 0,0,32,32 };
	int blockid=0;

};

int check_bcollisionH(SDL_Rect A, SDL_Rect B);
int check_bcollisionV(SDL_Rect A, SDL_Rect B);
int check_bcollision(SDL_Rect A, SDL_Rect B);