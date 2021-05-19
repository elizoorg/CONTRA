#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "Vector.h"
using namespace std;
class Player
{
public:
	Player();
	~Player();
	void Init(SDL_Renderer* render);
	void Update(vec2i Camerapos);
	void setState(int state);
	void setMirrored(bool mirr);
	void Draw(SDL_Renderer* render);
	void setGround(bool ground);
	void setJump(bool jump);
	vec2i getPos() { return worldpos; }
	int getPosX() { return worldpos.x; }
	int getPosY() { return worldpos.y; }
	int getPlayerWidth() {return clipRect.w;}
	void playerMove(int x, int y) {
		worldpos.x += x; worldpos.y += y;
	}
	void setPos(int x, int y) {
		worldpos.x = x;
		worldpos.y = y;
	}
	void setDamage() { damagetimer = 60; }
	int getDamage() { return damagetimer; }
	int playerGetHealth() { return health; };
	void changeHealth(int x) { health += x; }
	bool isDead() { return health > 0; }
	int getPlayerHeight() {return clipRect.h;}
	bool getGround() { return onGround; }
	SDL_Rect getRect() { return SDL_Rect{ worldpos.x,worldpos.y,90,150 }; }
	bool getMirrored() {return mirrored;}
	SDL_Rect getFlowRect() { return senseflow; }
	float getJumpSpeed() { return jumpSpeed; }
	int getPlayerFloorY() {  return (clipRect.y + clipRect.h); }
private:
	SDL_Texture* texture;
	SDL_Rect clipRect{ 300,340,90,150};
	SDL_Surface* s_player;
	SDL_Texture* heart;
	vec2i worldpos{ 500,0 };
	SDL_Rect senseflow = { 0,0,30,30 };
	SDL_Rect senseflowdraw{ 0,0,30,30 };
	SDL_Rect heartrect{ 0,0,60,60 };
	int heartrate = 0;
	SDL_Rect sourceRect{ 200,0,25,45 };
	int health = 3;
	int playerState;
	int dxSpeed=5;
	int damagetimer = 0;
	int dySpeed;
	int temp;
	bool mirrored;
	float gravity = -0.2f;
	float jumpSpeed;
	bool isJumped;
	bool onGround;
	int direction;
	int frameCounter = 0;
};

