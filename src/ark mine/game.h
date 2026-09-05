#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define START 1
#define EXIT  0

#define COL 9
#define ROW 9

#define COLS COL+2 
#define ROWS ROW+2 

#define ENEMY 40

void cleanScreen();
void menu();
void game();
void DispalyBoard(char board[ROWS][COLS], int row, int col);
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set);
struct PLAYER setPlayer();
struct ENE setEnemy(struct PLAYER *player);
void plot(char show[ROWS][COLS], int row, int col, struct PLAYER player);
void setmine(char board[ROWS][COLS], int row, int col);
void findmine(char board[ROWS][COLS], char showboard[ROWS][COLS], int row, int col, struct PLAYER *player);
int  countmine(char board[ROWS][COLS], int r, int c);

void event(struct PLAYER *player);
void shop(struct PLAYER* player);
void award(struct PLAYER* player);
void battle(struct PLAYER* player);
void print_battle(struct PLAYER* player, struct ENE* enemy,int round);
void playerturn(struct PLAYER* player, struct ENE* enemy,int round);
void enemyturn(struct PLAYER* player, struct ENE* enemy, int round);
void boss(struct PLAYER player);

void end_2();
void end_1();
void bad_end();

struct PLAYER {
	char name[60];
	int  hp;
	int  atk;
	int  shield;
	int  eco;
	int dec_e_atk;
	int nian;
	int eventnum;
	int enemynum;
	int day;
};
struct ENE {
	char name[60];
	int hp;
	int atk;
	int shield;
	int is_player_defend;
};
