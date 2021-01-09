#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<time.h>
#include"Game.h"
void PlayGame()
{
	int i;
	char board[ROW][COL] = { 0 };
	char is;
	IniBoard(board,ROW,COL);
	PrintBoard(board, ROW, COL);
	while (1)
	{
		PlayerMove(board, ROW, COL);
		is=IsEnd(board,ROW,COL);
		if (is != 1)
			break;
		ComputerMove(board, ROW, COL);
		is=IsEnd(board,ROW,COL);
		if (is != 1)
			break;
	}
	if (is == '*')
		printf("玩家获胜！\n");
	else if (is == '#')
		printf("电脑获胜！\n");
	else
		printf("平局！\n");
	printf("\n");
	printf("********************\n");
	printf("******是否继续******\n");
	printf("*****按1游戏继续*****\n");
	printf("*****任意键退出*****\n");
	printf("********************\n");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
		PlayGame();
		break;
	default:
		Exit();
		break;
	}
}
void Exit()
{
	printf("********************\n");
	printf("******游戏结束******\n");
	printf("****欢迎下次再来****\n");
	printf("********************\n");
}
void Menu()
{
	int i;
	srand(time(NULL));
	printf("*********************\n");
	printf("*****1.开始游戏******\n");
	printf("*****2.结束游戏******\n");
	printf("*********************\n");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
		PlayGame();
		break;
	case 2:
		Exit();
		break;
	default:
		Menu();
		break;
	}
}

int main()
{
	Menu();
	return 0;
}