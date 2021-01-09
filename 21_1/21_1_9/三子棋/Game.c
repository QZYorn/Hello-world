#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"Game.h"
void IniBoard(char board[ROW][COL], int row, int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}
void PrintBoard(char board[ROW][COL], int row, int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			if (j<col-1)
			{
				printf("|");
			}
			else
			printf("\n");
		}
		if (i<row-1)
		for (j = 0; j < col; j++)
		{
			printf("---");
			if (j < col - 1)
			{
				printf("|");
			}
			else
			printf("\n");
		}
	}
}
void PlayerMove(char board[ROW][COL], int row, int col)
{
	int i, j;
again:
	printf("玩家移动，输入>");
		scanf("%d %d", &i,&j);
		if (i > ROW || j > COL || i < 1 || j < 1)
		{
			printf("非法输入！请输入1至3的数\n");
			goto again;
		}
		else
		{
			if (board[i - 1][j - 1] == ' ')
			{
				board[i - 1][j - 1] = '*';
				PrintBoard(board, ROW, COL);
			}
			else
				printf("格子已被占用，请另寻高就。\n");
				goto again;
		}
		

		
}
void ComputerMove(char board[ROW][COL], int row, int col)
{
	int i, j;
again:
	i = rand() % 3;
	j = rand() % 3;
	if (board[i][j ] == ' ')
	{
		board[i][j] = '#';
		printf("电脑移动至（%d/%d）\n",i+1,j+1);
		PrintBoard(board, ROW, COL);
	}
	else
		goto again;
}
char IsEnd(char board[ROW][COL], int row, int col)
{
	int i,j;
	int count=0;
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
			return board[i][0];
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
				count++;
		}
	}
	for (j = 0; j < col; j++)
	{
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[1][j] != ' ')
			return board[0][j];
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
		return board[0][0];
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
		return board[0][2];
	if (count == 0)
		return ' ';
	return 1;
}
