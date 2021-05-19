#include "Player.h"

Player::Player()
{


}

Player::~Player()
{
	

}

void Player::Init(SDL_Renderer* render) {
	s_player = IMG_Load("player.png");
	if (!s_player) {
		printf("Error to upload gif file\n");
	}
	texture = SDL_CreateTextureFromSurface(render, s_player);
	if (!texture) {
		printf("Error to make texture from surface\n");
	}
	SDL_FreeSurface(s_player);
	s_player = IMG_Load("heart.png");
	if (!s_player) {
		printf("Error to upload gif file\n");
	}
	heart = SDL_CreateTextureFromSurface(render, s_player);
	if (!texture) {
		printf("Error to make texture from surface\n");
	}
	SDL_FreeSurface(s_player);
}

void Player::Update(vec2i Camerapos) {
	sourceRect.x= (frameCounter++ / 8) * 25;
	if (frameCounter > 11 * 8) frameCounter = 0;
	direction = mirrored ? -1 : 1;
	if (playerState && playerState!=2) worldpos.x += 5 * direction;
	if (worldpos.x < 0) worldpos.x += 5;
	if (worldpos.y >3200) health = 0;
	clipRect.x = worldpos.x - Camerapos.x;
	clipRect.y = worldpos.y - Camerapos.y;
	senseflow.x = worldpos.x+30;
	senseflow.y = worldpos.y + clipRect.h-30;
	senseflowdraw.x = senseflow.x - Camerapos.x;
	senseflowdraw.y = senseflow.y - Camerapos.y;
	if (!onGround) {
		playerState = 6;
		worldpos.y += jumpSpeed;
		jumpSpeed -= gravity;
	}
	else jumpSpeed = 0;
	if (damagetimer > 0) {
		temp = playerState;
		if (damagetimer % 2)
			playerState = 10;
		else playerState = temp;
		damagetimer--;
	}
	sourceRect.y = playerState * 45;
	if (isJumped && onGround) {
		isJumped = false;
		jumpSpeed = -10.0f;
		worldpos.y += jumpSpeed;
	}
	else isJumped = false;
}

void Player::setState(int state)
{
	playerState = state;
}

void Player::setMirrored(bool mirr)
{
	mirrored = mirr;
}

void Player::Draw(SDL_Renderer* render)
{
	if (mirrored)
		SDL_RenderCopyEx(render, texture, &sourceRect, &clipRect, 0, 0, SDL_FLIP_HORIZONTAL);
	else SDL_RenderCopy(render, texture, &sourceRect, &clipRect);
	SDL_SetRenderDrawColor(render, 255, 255, 0, 0);
	SDL_SetRenderDrawColor(render,0, 0, 0, 0);
	for (int i = 0; i < health; i++) {
		heartrect.x = i * 25;
		SDL_RenderCopy(render, heart,0,&heartrect);
	}
	
}

void Player::setGround(bool ground)
{
	onGround = ground;
}

void Player::setJump(bool jump)
{
	isJumped = jump;
}
