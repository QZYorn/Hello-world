#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
void initboard(char board[ROWS][COLS], char n)
{
	int rows,cols;
	for (rows=0; rows < ROWS; rows++)
	{
		for (cols=0; cols < COLS; cols++)
		{
			board[rows][cols] = n;
		}
	}
}
void revealboard(char board[ROWS][COLS])
{
	int row = 1;
	int col = 1;
	int num = Num_open(board);
	printf("\n*******剩余格子数%2d///////雷的数量%2d********\n", num,MINES);
	printf("     ");
	for (col=1; col <= COL; col++)
	{
		printf(" %2d ",col);
	}
	printf("\n     ");
	for (col=1; col <= COL; col++)
	{
		printf("====");
	}
	printf("\n");
	for (row=1; row <= ROW*2; row++)
	{
		if (row % 2 == 0)
		{
			printf("    |\n");
		}
		if (row % 2 == 1)
		{
			printf(" %2d |", (row + 1) / 2);

			for (col = 1; col <= COL; col++)
			{
				printf(" %2c ", board[(row + 1) / 2][col]);
			}
			printf("\n");
		}
	}
}
void lay_mine(char origin[ROWS][COLS],int mine_num)
{
	int row, col;
	for (; mine_num > 0; mine_num--)
	{
		row = rand() % ROW + 1;
		col = rand() % COL + 1;
		if (origin[row][col] != '1')
		{
			origin[row][col] = '1';
		}
	}
}
void clear_mine(char origin[ROWS][COLS], char show[ROWS][COLS])
{
	int i, j;
	int count = Num_open;//统计未展开格子数
	while (count>MINES)
	{
again:
		printf("请输入坐标（行/列）=>");
		scanf("%d%d", &i,&j);
		if (i > 0 && j > 0 && i <= ROW&&j <= COL)
		{
			if (origin[i][j] !='1')
			{
				//revealboard(origin);//调试用
				Find_mine(origin,show,i,j);//寻找周围八格雷数
				revealboard(show);//显示 表雷盘
				count = Num_open(show);//统计未展开格子数
			}
			else
			{
				break;
			}
		}
		else
		{
			printf("非法输入！！！\n");
			goto again;
		}

	}
	if (count == MINES)
	{
		printf("恭喜！您已排查出所有的雷!\n");
		printf("雷阵布局如下:\n");
		revealboard(origin);
		return;
	}
	printf("砰！！！！！！！！！\n");
	Sleep(500);
	printf("砰！！！！！！！！！！！\n");
	Sleep(500);
	printf("砰！！！！！！！！！！！！！\n");
	Sleep(500);
	printf("砰！！！！！！！！！！！！！！！\n");
	Sleep(500);
	printf("很遗憾，GameOv——er\n");
	Sleep(1000);
}
void Find_mine(char origin[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	int ret = Num_mine(origin, x, y);
	if (ret == 0 && show[x][y] == '*')
	{
		show[x][y] = ' ';
		if (x - 1 > 0  && y - 1 > 0   && show[x - 1][y - 1] == '*')// 左上方
			Find_mine(origin, show, x - 1, y - 1);
		if (x - 1 > 0  && y     > 0   && show[x - 1][y] == '*')//上方
			Find_mine(origin, show, x-1, y );
		if (x - 1 > 0  && y + 1 <=COL && show[x - 1][y + 1] == '*')//右上方
			Find_mine(origin, show, x - 1, y + 1);
		if (x     > 0  && y + 1 <=COL && show[x][y + 1] == '*')//右方
			Find_mine(origin, show, x, y + 1);
		if (x + 1 <=ROW&& y + 1 <=COL && show[x + 1][y + 1] == '*')//右下方
			Find_mine(origin, show, x + 1, y + 1);
		if (x + 1 <=ROW&& y     > 0   && show[x + 1][y] == '*')//下方
			Find_mine(origin, show, x + 1, y);
		if (x + 1 <=ROW&& y - 1 > 0   && show[x + 1][y - 1] == '*')//左下方
			Find_mine(origin, show, x + 1, y - 1);
		if (x     > 0  && y - 1 <=COL && show[x][y - 1] == '*')//左方
			Find_mine(origin, show, x, y - 1);
	}
	else
		show[x][y] = ret + '0';
}
int Num_mine(char origin[ROWS][COLS],int x,int y)
{
	return
		origin[x - 1][y - 1] +
		origin[x - 1][y] +
		origin[x - 1][y + 1] +
		origin[x][y - 1] +
		origin[x][y + 1] +
		origin[x + 1][y - 1] +
		origin[x + 1][y] +
		origin[x + 1][y + 1]
		- 8 * '0';
}
int Num_open(char show[ROWS][COLS])
{
	int x, y, n;
	n = 0;
	for (x = 1; x <= ROW; x++)
	{
		for (y = 1; y <= COL; y++)
		{
			if (show[x][y]=='*')
			{
				n++;
			}
		}
	}
	return n;
}