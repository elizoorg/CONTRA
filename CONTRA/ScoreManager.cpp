#include "ScoreManager.h"



void ScoreManager::update()
{
	int c = 0;
	bool flag = 1;
	FILE* file1;
	if ((file1 = fopen("scores", "rb")) == NULL)
	{
		if ((file1 = fopen("scores", "wb")) == NULL)
		{
			perror("Error create file");
			return;
		}
		return;
	}
	FILE* file2;
	if ((file2 = fopen("score1", "wb")) == NULL)
	{
		perror("Error create file");
		return;
	}
	while (flag && c < 9) //Всего в файле может быть 9 записей,для простоты и контроля данных
	{
		flag = fread(&player_score, sizeof(player_score), 1, file1);
		if (flag)
		{
			if (player_score.sec < player.sec)
				fwrite(&player_score, sizeof(player_score), 1, file2);
			else
			{
				if (player.sec)
				{
					fwrite(&player, sizeof(player), 1, file2);
					fwrite(&player_score, sizeof(player_score), 1, file2);
					player.sec = 0;
				}
				else
					fwrite(&player_score, sizeof(player_score), 1, file2);
				//Читаем данные из 1-го файла и записываем во второй,вставляем нашу запись в нужном порядке сравнивая с текущими очками
			}
		}
		else
		{
			if (player.sec)
			{
				fwrite(&player, sizeof(player), 1, file2);
				player.sec = 0;
			}
		}
		c++;
	}
	fclose(file2);
	fclose(file1);
	remove("scores");
	rename("score1", "scores");
}

void ScoreManager::reset()
{
	player.sec = 0;
}

void ScoreManager::draw(SDL_Renderer* Render)
{
	FILE* file1;
	SDL_Color color_fon{ 158,209,48 };
	char buf[25] = {};
	bool quit;
	SDL_Event event;
	SDL_Rect r{ 100,200,0,0 };
	TTF_Font* font;
	font = TTF_OpenFont("CharisSILR.ttf", 48);
	SDL_Surface* text_surface;
	SDL_Texture* text;
	bool end = false;
	if (!(file1 = fopen("scores", "rb"))) //Если файл не открыт напишется ошибка на экране
	{
		text_surface = TTF_RenderUTF8_Solid(font, "Error to open a file!", color_fon);
		r.w = text_surface->w;
		r.h = text_surface->h;
		text = SDL_CreateTextureFromSurface(Render, text_surface);
		SDL_RenderCopy(Render, text, NULL, &r);
		SDL_RenderPresent(Render);
		SDL_Delay(2000);
		return;
	}
	SDL_SetRenderDrawColor(Render, 153, 153, 255, 0); //Тут поменять цвета!!!
	SDL_Rect rr = { 499, 214, 920, 520 };
	SDL_Rect rr1 = { 509, 224, 900, 500 };
	SDL_RenderFillRect(Render, &rr);
	SDL_SetRenderDrawColor(Render, 230, 230, 255, 0);
	SDL_RenderFillRect(Render, &rr1);
	r.y = 224;
	SDL_SetRenderDrawColor(Render, 0, 0, 0, 0);

	if (file1)
	{
		rewind(file1);
		while (fread(&player_score, sizeof(player_score), 1, file1))
		{
			r.x = 519;
			if(strlen(player_score.Name))
			sprintf(buf, "%s", player_score.Name);
			else sprintf(buf, "%s","Unknown");
			text_surface = TTF_RenderUTF8_Solid(font, buf, color_fon);
			r.w = text_surface->w;
			r.h = text_surface->h;
			text = SDL_CreateTextureFromSurface(Render, text_surface);
			SDL_FreeSurface(text_surface);
			SDL_RenderCopy(Render, text, NULL, &r);
			r.x = 979;
			sprintf(buf, "%d", player_score.sec);
			text_surface = TTF_RenderUTF8_Solid(font, buf, color_fon);
			r.w = text_surface->w;
			r.h = text_surface->h;
			text = SDL_CreateTextureFromSurface(Render, text_surface);
			SDL_FreeSurface(text_surface);
			SDL_RenderCopy(Render, text, NULL, &r);
			r.y += 50;
			SDL_DestroyTexture(text);
		}
		fclose(file1);

	}
	TTF_CloseFont(font);
	SDL_RenderPresent(Render);
}

ScoreManager::ScoreManager()
{
}

ScoreManager::~ScoreManager()
{
}
