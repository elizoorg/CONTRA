#pragma once
#include <SDL.h>
#include "Score.h"
#include <cstdio>
#include <string.h>
#include "SDL_ttf.h"
class ScoreManager
{
public:
	void update();
	void reset();
	void draw(SDL_Renderer* Render);
	ScoreManager();
	~ScoreManager();
private:

};

