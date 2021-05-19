#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Control.h"
#include "Timer.h"
#include "Bullet.h"
#include "Alien.h"
#include <fstream>
#include "Block.h"
#include "ScoreManager.h"
#include "Player.h"
#include "MAp.h"
#include "Camera.h"
#include "Log.h"
#include "TextDrawer.h"
#include "Coins.h"
using namespace std;
#define FRAME_RATE 60
class Game
{
public:
	Game();
	~Game();
	void Init();
	void Draw();
	void Play();
	void PauseMode();
	void Start();
	void End();
	void Menu();
	void Loop();
private:
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Event event;
	bool end = false;
	Uint32 start;
	EventHandler* handler;

	Player player1;

	SDL_Rect line{ 0,690,1080,1 };
	SDL_Rect line1{ 0,500,1080,1 };
	Timer* timer_;

	Bullet bull;
	vector <Bullet*> bullets;

	Block block;
	SDL_Rect r;
	vector <SDL_Rect*> blocks;

	vector <Alien*> aliens;

	SDL_Rect screen{ 0,0,1280,1024 };

	int damagetimer = 0;

	SDL_Texture* background;
	SDL_Surface* temp;
	SDL_Texture* background1;
	Map mymap;

	ScoreManager manage;

	int angle;
	int dtime = 0;

	int s=0,k=0,q;

	Camera camera;
	bool extr = false;

	bool win = false;

	Alien alien;
	Uint32 ticks;
	int min;
	int sec;

	TextDrawer textdrawer;
	int coinscount=0;
	int aliencount=0;


	Coins coin;
	vector<Coins*> coins;



	int map[54][200];
	ifstream mapfile;
	char ch;
	int m = 0, n = 0;
	SDL_Texture* tilemap;
	SDL_Surface* s_player;
	SDL_Rect r3{ 0,0,32,32 };
	SDL_Rect r4{ 0,0,16,16 };
};

