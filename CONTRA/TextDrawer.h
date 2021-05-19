#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
using namespace std;
class TextDrawer
{
public:
	TextDrawer();
	~TextDrawer();
	void InitFont(string str);
	void DrawText(SDL_Renderer* render,string str,int x,int y);
	void DrawInt(SDL_Renderer* render,int a, int x, int y);
private:
	TTF_Font* font;
	SDL_Color color{ 255,255,255 };
	SDL_Surface* temp;
	SDL_Texture* text;
	SDL_Rect clipRect;
};

