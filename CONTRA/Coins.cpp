#include "Coins.h"

Coins::Coins()
{
}

Coins::~Coins()
{
}

void Coins::Init(SDL_Renderer* render)
{
	surf = IMG_Load("coin.png");
	if (!surf) {
		printf("Error to upload gif file\n");
	}
	texture = SDL_CreateTextureFromSurface(render, surf);
	if (!texture) {
		printf("Error to make texture from surface\n");
	}
	SDL_FreeSurface(surf);
}

void Coins::Update(vec2i camerapos)
{
	sourceRect.x = (frameCounter++ / 8) * sourceRect.w;
	if (frameCounter > 4 * 8) frameCounter = 0;
	clipRect.x = worldpos.x - camerapos.x;
	clipRect.y = worldpos.y - camerapos.y;
}

void Coins::Draw(SDL_Renderer* render)
{
	SDL_RenderCopy(render, texture, &sourceRect, &clipRect);
}
