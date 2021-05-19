#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Vector.h"
#include <SDL_image.h>
using namespace std;
class Map
{
public:
	Map();
	~Map();
	void loadMap(string path,int w,int h);
	vector <SDL_Rect*> getMap() { return map; };
	void DrawMap(SDL_Renderer* render,vec2i camera);
	void loadTileMap(SDL_Renderer* render, string str);
private:
	SDL_Rect clipRect{ 0,0,16,16};
	SDL_Rect testrect{ 0,0,64,64};
	vector <SDL_Rect*> map;
	vector <int> id;
	ifstream mapfile;
	SDL_Rect sourceRect;
	SDL_Texture* tilemap;
	SDL_Surface* temp;
	char ch;
	int n;
	int i, j;
};

