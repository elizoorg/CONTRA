
#include "Game.h"
#include "score.h"



Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

Game::~Game()
{
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(background1);
	SDL_DestroyWindow(window);
	bullets.clear();
	coins.clear();
	aliens.clear();
	SDL_Quit();
	TTF_Quit();
}

void Game::Init()
{
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		printf("%s\n", SDL_GetError());
		SDL_Quit();
		return;
	}
	TTF_Init();
	window = SDL_CreateWindow("Contra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 1024, 0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	player1.Init(render);
	coin.Init(render);
	player1.setPos(0, 0);
	alien.Init(render, "alien.png", 320, 64 * 17-12, 300, 640);
	aliens.push_back(new Alien(alien));
	alien.Init(render, "alien2.png", 1540, 64 * 23-12,1420, 1600);
	aliens.push_back(new Alien(alien));
	alien.Init(render, "alien3.png", 2630, 64 * 34-12, 2500, 2700);
	aliens.push_back(new Alien(alien));
	alien.Init(render, "ysatiichert.png", 6400, 64 * 39-12, 6100, 6840);
	aliens.push_back(new Alien(alien));
	
	coin.SetPos(vec2i(2880, 6 * 64-5));
	coins.push_back(new Coins(coin));
	coin.SetPos(vec2i(9730, 40 * 64-5));
	coins.push_back(new Coins(coin));

	temp = IMG_Load("background.png");
	background = SDL_CreateTextureFromSurface(render, temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("background1.png");
	background1 = SDL_CreateTextureFromSurface(render, temp);
	SDL_FreeSurface(temp);


	mymap.loadMap("map151.csv",200,54);
	mymap.loadTileMap(render, "tilemap.png");
	blocks = mymap.getMap();

	textdrawer.InitFont("CharisSILR.ttf");

	bull.setTexture(render);
}

void Game::Draw()
{
	SDL_SetRenderDrawColor(render, 135, 206, 235, 0);
	SDL_RenderClear(render);
	
	textdrawer.DrawInt(render, (sec + 60)%3000/50, 645, 0);
	textdrawer.DrawText(render, ":",625, 0);
	textdrawer.DrawInt(render, (sec + 60) /3000, 565, 0);
	for (size_t t = 0; t < bullets.size(); t++)
		bullets[t]->Draw(render,camera.getPos());
	SDL_SetRenderDrawColor(render, 0, 255, 0, 0);
	mymap.DrawMap(render,camera.getPos());
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	for (size_t t = 0; t < coins.size(); t++)
		coins[t]->Draw(render);
	for(size_t t = 0 ; t < aliens.size(); t++)
	aliens[t]->Draw(render, camera.getPos());
	player1.Draw(render);
	SDL_RenderPresent(render);
}

void Game::PauseMode() {
	bool endless = false;
	textdrawer.DrawText(render, u8"Шифт - продолжить,CTRL - выход", 230, 400);

	textdrawer.DrawText(render, u8"Монстры", 930, 0);
	textdrawer.DrawInt(render, aliencount / 124, 1210, 0);
	textdrawer.DrawText(render, "/", 1230, 0);
	textdrawer.DrawInt(render, aliens.size(), 1250, 0);

	textdrawer.DrawText(render, u8"Монетки", 930, 70);
	textdrawer.DrawInt(render, coinscount, 1210, 70);
	
	textdrawer.DrawText(render, "/", 1230, 70);
	textdrawer.DrawInt(render, coins.size(), 1250, 70);
	SDL_RenderPresent(render);
	while (!endless)
		while (SDL_PollEvent(&event)) {
			handler->Handle(&event);
			if (handler->KeyDown(SDLK_LSHIFT)) endless = true;
			if (handler->KeyDown(SDLK_LCTRL)) { end = true; endless = true; extr = true; }
		}
}

void Game::Play()
{
	sec++;
	if (dtime < 15) dtime++;
	if (handler->KeyDown(SDLK_ESCAPE)) { PauseMode();}
	if (handler->KeyDown(SDLK_a) || handler->KeyDown(SDLK_d)) {
	if (handler->KeyDown(SDLK_a)) {player1.setMirrored(true); angle = 180;}
	else if (handler->KeyDown(SDLK_d)) {player1.setMirrored(false); angle = 0;}
	if (handler->KeyDown(SDLK_w)) {player1.setState(4);angle += (45 * (player1.getMirrored() ? 1:-1));}
	else if (handler->KeyDown(SDLK_s)) {
	player1.setState(5); angle -= (45 * (player1.getMirrored() ? 1 : -1));}
	else if (handler->KeyDown(SDLK_LSHIFT)) player1.setState(3);
	else {player1.setState(1);}}
	else if (handler->KeyDown(SDLK_w)) {player1.setState(2);  angle = 270;}
	else {player1.setState(0); angle = player1.getMirrored() ? 180 : 0;}


	for (size_t t = 0; t < blocks.size(); t++) {
		
		if (check_bcollisionH(player1.getRect(), *blocks[t]) == 2) {
			player1.playerMove(blocks[t]->x - player1.getRect().x - player1.getRect().w , 0);
			

			continue;

		}
		if (check_bcollisionH(player1.getRect(), *blocks[t]) == 1) {
			player1.playerMove(blocks[t]->x - player1.getRect().x + player1.getRect().w , 0);
			
			continue;

		}
	}


	
	for (size_t t = 0; t < blocks.size(); t++) {	
		if (check_bcollisionV(player1.getRect(), *blocks[t]) == 1)
		{
			player1.playerMove(0, blocks[t]->h + blocks[t]->y - player1.getRect().y - player1.getRect().h);
			
			continue;
		}
		if (check_bcollisionV(player1.getFlowRect(), *blocks[t])==2 )
		{
			player1.playerMove(0, blocks[t]->y - player1.getRect().y - player1.getRect().h + 10);
			
			player1.setGround(true);		
			break;		
		}
		player1.setGround(false);		
	}

	if (player1.getGround()) {
		if (handler->KeyDown(SDLK_SPACE)) {
			player1.playerMove(0, -12);
			player1.setJump(true);
		}
	}
	for (size_t t = 0; t < aliens.size(); t++)
	aliens[t]->Update();
	for(size_t t = 0; t < coins.size(); t++)
		coins[t]->Update(camera.getPos());
	player1.Update(camera.getPos());
	camera.Update(player1.getPos());
	for (size_t t = 0; t < aliens.size(); t++)
	if (check_bcollision(player1.getRect(), aliens[t]->getRect()) && !player1.getDamage() && !aliens[t]->Dead() ) {
		player1.setDamage();
		player1.changeHealth(-1);  
	}
	if (damagetimer > 0)damagetimer--;
	for (size_t m = 0; m < aliens.size(); m++)
	for (size_t t = 0; t < bullets.size(); t++) {
		if (check_bcollision(bullets[t]->getRect(), aliens[m]->getRect())) {
			bullets.erase(bullets.begin() + t); aliens[m]->changeHealth(1); aliens[m]->setState(alien.HURT);

		} 
	}
	for (size_t t = 0; t < aliens.size(); t++)
	if (aliens[t]->Dead()) {
		aliencount++;
		aliens[t]->setState(alien.DEAD);
	}
	for (size_t t = 0; t < coins.size(); t++) {
		if (check_bcollision(player1.getRect(), coins[t]->getRect())) {
			coins[t]->SetPos(vec2i(0, 0));
		
			cout << coinscount << endl;
			coinscount++;
			cout << coinscount << endl;
		}
	}
	

	if (handler->KeyDown(SDLK_LSHIFT)) {
		if (dtime > 13 && player1.getGround()) {
			bull.setPos(vec2i(player1.getPosX() + player1.getPlayerWidth() / 2 + 40 * cos(angle * 3.14 / 180),player1.getPosY() + player1.getPlayerHeight() / 2 + 60 * sin(angle * 3.14 / 180)));
			bull.setAngle(angle);
			bullets.push_back(new Bullet(bull));
			dtime = 0;
		}
	}

	for (size_t t = 0; t < bullets.size(); t++)
		bullets[t]->Move();
	for (size_t m = 0; m < blocks.size(); m++) {
		for (size_t t = 0; t < bullets.size(); t++) {
			if (check_bcollision(bullets[t]->getRect(), *blocks[m])) {
				bullets.erase(bullets.begin() + t);
			}
		}
	}
	if (!player1.isDead()) {
		end = true; win = false;
	}
	if (coinscount == coins.size() && aliencount / 124 == aliens.size()) { end = true; win = true; }
}

void Game::Start()
{
	Init();	
	handler = EventHandler::Instance();
	Menu();
	timer_ = Timer::Instance();
	start = SDL_GetTicks();
	while (!end) {	
		Loop();
	}
	End();

}

void Game::End() {

	bool endless = true;

	SDL_RenderCopy(render, background1, 0, 0);
	textdrawer.DrawText(render, u8"Монстров убито", 450, 610);
	textdrawer.DrawInt(render, aliencount / 124, 930, 610);
	textdrawer.DrawText(render, "/", 980, 610);
	textdrawer.DrawInt(render, aliens.size(), 1030, 610);
	textdrawer.DrawText(render, u8"Монеток собрано", 450, 670);
	textdrawer.DrawInt(render, coinscount, 930, 670);
	textdrawer.DrawText(render, "/", 980, 670);
	textdrawer.DrawInt(render, coins.size(), 1030, 670);
	textdrawer.DrawText(render, extr?u8"Потрачено зря":u8"Времени потрачено", 450, 730);
	textdrawer.DrawInt(render, (sec + 60) % 3000 / 50, 1030, 730);
	textdrawer.DrawText(render, ":", 980, 730);
	textdrawer.DrawInt(render, (sec + 60) / 3000, 930, 730);
	textdrawer.DrawText(render, win?u8"Вы выйграли":extr?u8"Вы струсили!":u8"Вы проиграли", 450, 540);
	SDL_RenderPresent(render);

	while (endless) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { end = true; endless = true; }
			handler->Handle(&event);
		}
		if (handler->KeyDown(SDLK_RETURN)) endless = false;
	}
	player.sec = sec;
	if (win) {
		int m = 1; //После того как проиграли переходим к выбору имени ( как на старых игровых автоматах)
		SDL_Surface* feed = IMG_Load("name.png");
		bool done = true;
		SDL_Texture* nname = SDL_CreateTextureFromSurface(render, feed);
		SDL_FreeSurface(feed);
		string s;
		SDL_RenderCopy(render, nname, 0, 0);
		while (done)
		{
			while (SDL_PollEvent(&event)) {
				switch (event.type)
				{
				case SDL_QUIT:
					done = true;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_ESCAPE) done = false; //Смена букв
					if (event.key.keysym.sym == SDLK_s) {
						player.Name[m - 1]++; SDL_RenderClear(render); SDL_RenderCopy(render, nname, 0, 0);
					}
					else if (event.key.keysym.sym == SDLK_w){ player.Name[m - 1]--; SDL_RenderClear(render); SDL_RenderCopy(render, nname, 0, 0);
					}
					else if (event.key.keysym.sym == SDLK_a) m--;
					else if (event.key.keysym.sym == SDLK_d) m++;
					if (m < 1) m = 1;
					if (m > 3) m = 3;
					if (player.Name[m - 1] < 'A') player.Name[m - 1] = 'Z';
					if (player.Name[m - 1] > 'Z') player.Name[m - 1] = 'A';
					break;
				default:
					break;
				}
			}
			
			s = player.Name[0];
			textdrawer.DrawText(render,s,480,480);
			s = player.Name[1];
			textdrawer.DrawText(render,s,610,480);
			s = player.Name[2];
			textdrawer.DrawText(render,s,740,480);		
			SDL_RenderPresent(render);
		} 
		manage.update();
		SDL_DestroyTexture(nname);




	}



}

void Game::Menu()
{
	bool endless = true;
	SDL_RenderCopy(render, background, 0, 0);
	SDL_RenderPresent(render);

	while (endless) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { end = true; endless = true; }
			handler->Handle(&event);
		}
		if (handler->KeyDown(SDLK_RETURN)) endless = false;
		if (handler->KeyDown(SDLK_LSHIFT)) {
			FILE* file1;
			SDL_Color color_fon{ 0,255,255 };
			char buf[10] = {};
			bool quit;
			SDL_Event event;
			SDL_Rect r{ 100,200,0,0 };
			TTF_Font* font;
			font = TTF_OpenFont("font.ttf", 48);
			SDL_Surface* text_surface;
			SDL_Texture* text;
			cout << 1 << endl;
			bool end = false;
			SDL_RenderClear(render);
			if (!(file1 = fopen("scores", "rb"))) //Если файл не открыт напишется ошибка на экране
			{
				text_surface = TTF_RenderUTF8_Solid(font, "Error to open a file!", color_fon);
				r.w = text_surface->w;
				r.h = text_surface->h;
				text = SDL_CreateTextureFromSurface(render, text_surface);
				SDL_RenderCopy(render, text, NULL, &r);
				SDL_RenderPresent(render);
				SDL_Delay(2000);
				cout << 1 << endl;
				return;
			}
			SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
			SDL_RenderClear(render);//Рамка
			r.y = 125;
			text_surface = TTF_RenderUTF8_Solid(font, "Scores", color_fon);
			r.w = text_surface->w;
			r.x = 450 - r.w / 2;
			cout << 1 << endl;
			r.h = text_surface->h;
			text = SDL_CreateTextureFromSurface(render, text_surface);
			SDL_FreeSurface(text_surface);
			SDL_RenderCopy(render, text, NULL, &r);

			SDL_SetRenderDrawColor(render, 95, 75, 139,0);
			SDL_Rect rr = { 325,175,615,635 };
			SDL_Rect rr1 = { 340,185,585,615 };
			SDL_RenderFillRect(render, &rr);
			SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
			SDL_RenderFillRect(render, &rr1);
			cout << 1 << endl;
			r.y = 200;

			if (file1) //Если файл открыт пишем в виде  : <<Имя		очки	время>>
			{
				rewind(file1);
				string z;
				while (fread(&player_score, sizeof(player_score), 1, file1))
				{				
					cout << player_score.Name[0] << player_score.Name[1] << player_score.Name[2] << " " << sec << endl;
					z = "";
					z += player_score.Name[0];
					z += player_score.Name[1];
					z+=player_score.Name[2];
					textdrawer.DrawText(render, z, 350, r.y);
					textdrawer.DrawInt(render, (player_score.sec + 60) % 3000 / 50, 750, r.y);
					textdrawer.DrawText(render,":", 700, r.y);
					textdrawer.DrawInt(render, (player_score.sec + 60) / 3000, 650, r.y);
					r.y += 50;
				
				}

				fclose(file1);

			}
			
			SDL_Event event1;
			textdrawer.DrawText(render, "Press enter to start the game", 300, 850);
			SDL_RenderPresent(render);
			bool endles = true;
			while (!endles) {
				while (SDL_PollEvent(&event1)) {
					switch (event1.type)
					{
					case SDL_QUIT:
						end = true;
						break;
					case SDL_KEYDOWN:
						if (event1.key.keysym.sym == SDLK_RETURN || event1.key.keysym.sym == SDLK_ESCAPE) {
							endles = false; 	
						}
					
						//Пока не нажали enter или escape мы не выйдем в главное меню

						break;
					default:
						break;
					}
				}

			}
		}
	}
	
}

void Game::Loop()
{
	timer_->Update();
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) end = true;
		handler->Handle(&event);
	}
	
	if (timer_->DeltaTime() >= 1.0f / FRAME_RATE) {
		Play();
		Draw();
		timer_->Reset();
	}
}
