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
		printf("��һ�ʤ��\n");
	else if (is == '#')
		printf("���Ի�ʤ��\n");
	else
		printf("ƽ�֣�\n");
	printf("\n");
	printf("********************\n");
	printf("******�Ƿ����******\n");
	printf("*****��1��Ϸ����*****\n");
	printf("*****������˳�*****\n");
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
	printf("******��Ϸ����******\n");
	printf("****��ӭ�´�����****\n");
	printf("********************\n");
}
void Menu()
{
	int i;
	srand(time(NULL));
	printf("*********************\n");
	printf("*****1.��ʼ��Ϸ******\n");
	printf("*****2.������Ϸ******\n");
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