#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

#define MINES 10


void initboard(char board[ROWS][COLS], char n);
void revealboard(char board[ROWS][COLS]);
void lay_mine(char origin[ROWS][COLS], int mine_num);
void clear_mine(char origin[ROWS][COLS], char show[ROWS][COLS]);
void Find_mine(char origin[ROWS][COLS], char show[ROWS][COLS],int x,int y);
int Num_mine(char origin[ROWS][COLS],int x,int y);
int Num_open(char show[ROWS][COLS]);
