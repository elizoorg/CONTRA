#pragma once
struct Score { //Структура игрока
	char Name[3] = { 'A','A','A' };
	int sec = 0;
};
extern struct Score player;
extern struct Score player_score;