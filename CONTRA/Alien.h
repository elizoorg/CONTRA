#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "vector.h"
#include <iostream>
using namespace std;
class Alien
{
public:
	Alien();
	~Alien();
	enum STATES { WALK, HURT, DEAD, STAY };
	void setPos(int x, int y) {
		worldpos.x = x;
		worldpos.y = y;
	}
	void setBorders(int x, int y) {
		
	}
	void setDist(vec2i playerpos) {
		dist = sqrt((playerpos.x - worldpos.x) * (playerpos.x - worldpos.x) + (playerpos.y - worldpos.y) * (playerpos.y - worldpos.y));
	}
	void Update() {
		if (state != DEAD) {
			sourceRect.x = (frame++ / 3) * 64;
			sourceRect.y = state * 128;
			if (frame > 11 * 3)frame = 0;
		}
		if (state == WALK) {
			worldpos.x += speed;
			if (worldpos.x<borders.x || worldpos.x > borders.y) speed *= -1;
		}
		if (state == HURT) {
			if (!count) {
				frame = 0; count++;
			}
			if (frame > 11 * 3 - 1) {
				count = 0; state = WALK;
			}

		}
		if (state == DEAD) {
			sourceRect.w = 128;
			sourceRect.h = 128;
			clipRect.w = 128;
			sourceRect.x = (frame++ / 30) * 128;
			sourceRect.y = state * 128;
			if (frame > 5 * 30) {
				setPos(-100, -100);
				health = 1;
			}
		}
	};
	void changeHealth(int a) { health -= a; }
	bool Dead() { return health < 0; }
	int GetState() {
		return state;
	}
	void setState(int x) { state = x; }
	vec2i getPos() { return worldpos; }
	void Init(SDL_Renderer* render, string str, int x, int y, int x1, int x2) {
		temp = IMG_Load(str.c_str());
		texture = SDL_CreateTextureFromSurface(render, temp);
		SDL_FreeSurface(temp);
		worldpos.x = x; worldpos.y = y;
		borders.x = x1; borders.y = x2;
	}
	void Draw(SDL_Renderer* render, vec2i camerapos);
	void setTexture(SDL_Renderer* render,string str);
	SDL_Rect getRect() { return SDL_Rect{ worldpos.x,worldpos.y,90,150 }; }

private:
	int frame = 0;
	int count = 0;
	int speed =2;
	float dist;
	int state = WALK;
	int health = 5;
	vec2i worldpos;
	SDL_Texture* texture;
	SDL_Surface* temp;
	vec2i borders;
	SDL_Rect clipRect = { 0,0,90,150 };
	SDL_Rect sourceRect = { 0,0,64,128 };
};

