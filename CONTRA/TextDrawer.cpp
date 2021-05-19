#include "TextDrawer.h"
#include <string>

TextDrawer::TextDrawer()
{
}

TextDrawer::~TextDrawer()
{
}

void TextDrawer::InitFont(string str)
{
	font = TTF_OpenFont(str.c_str(), 48);
}

void TextDrawer::DrawText(SDL_Renderer* render,string str, int x, int y)
{
	temp = TTF_RenderUTF8_Solid(font, str.c_str(),color);
	text = SDL_CreateTextureFromSurface(render, temp);
	SDL_Rect rect{ x,y,temp->w,temp->h };
	SDL_RenderCopy(render, text, 0, &rect);
	SDL_FreeSurface(temp);
	SDL_DestroyTexture(text);

}

void TextDrawer::DrawInt(SDL_Renderer* render, int a, int x, int y)
{
	temp = TTF_RenderUTF8_Solid(font, to_string(a).c_str(), color);
	text = SDL_CreateTextureFromSurface(render, temp);
	SDL_Rect rect{ x,y,temp->w,temp->h };
	SDL_RenderCopy(render, text, 0, &rect);
	SDL_FreeSurface(temp);
	SDL_DestroyTexture(text);
	
}
