#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
	map.clear();
}

void Map::loadMap(string path,int w,int h)
{
	mapfile.open(path);
	if (!mapfile) cout << "Error to open file";
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			mapfile >> n;
			mapfile >> ch;
			if (n == -1) continue;
			testrect.x = j * 64;
			testrect.y = i * 64;
			id.push_back(n);
			map.push_back(new SDL_Rect(testrect));
		}
	}

	mapfile.close();
}

void Map::loadTileMap(SDL_Renderer* render,string str)
{
	temp = IMG_Load(str.c_str());
	tilemap = SDL_CreateTextureFromSurface(render, temp);
	SDL_FreeSurface(temp);
}

void Map::DrawMap(SDL_Renderer* render, vec2i cameraX)
{
	for (size_t t = 0; t < map.size(); t++) {
		clipRect.x = (id[t] % 16) * 16; 
		clipRect.y = (id[t] / 16) * 16;
		SDL_Rect rect{ map[t]->x - cameraX.x,map[t]->y - cameraX.y,map[t]->w,map[t]->h };
		SDL_RenderCopy(render, tilemap, &clipRect, &rect);
	}
}
