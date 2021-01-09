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
	printf("\n*******ʣ�������%2d///////�׵�����%2d********\n", num,MINES);
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
	int count = Num_open;//ͳ��δչ��������
	while (count>MINES)
	{
again:
		printf("���������꣨��/�У�=>");
		scanf("%d%d", &i,&j);
		if (i > 0 && j > 0 && i <= ROW&&j <= COL)
		{
			if (origin[i][j] !='1')
			{
				//revealboard(origin);//������
				Find_mine(origin,show,i,j);//Ѱ����Χ�˸�����
				revealboard(show);//��ʾ ������
				count = Num_open(show);//ͳ��δչ��������
			}
			else
			{
				break;
			}
		}
		else
		{
			printf("�Ƿ����룡����\n");
			goto again;
		}

	}
	if (count == MINES)
	{
		printf("��ϲ�������Ų�����е���!\n");
		printf("���󲼾�����:\n");
		revealboard(origin);
		return;
	}
	printf("�飡����������������\n");
	Sleep(500);
	printf("�飡��������������������\n");
	Sleep(500);
	printf("�飡������������������������\n");
	Sleep(500);
	printf("�飡����������������������������\n");
	Sleep(500);
	printf("���ź���GameOv����er\n");
	Sleep(1000);
}
void Find_mine(char origin[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	int ret = Num_mine(origin, x, y);
	if (ret == 0 && show[x][y] == '*')
	{
		show[x][y] = ' ';
		if (x - 1 > 0  && y - 1 > 0   && show[x - 1][y - 1] == '*')// ���Ϸ�
			Find_mine(origin, show, x - 1, y - 1);
		if (x - 1 > 0  && y     > 0   && show[x - 1][y] == '*')//�Ϸ�
			Find_mine(origin, show, x-1, y );
		if (x - 1 > 0  && y + 1 <=COL && show[x - 1][y + 1] == '*')//���Ϸ�
			Find_mine(origin, show, x - 1, y + 1);
		if (x     > 0  && y + 1 <=COL && show[x][y + 1] == '*')//�ҷ�
			Find_mine(origin, show, x, y + 1);
		if (x + 1 <=ROW&& y + 1 <=COL && show[x + 1][y + 1] == '*')//���·�
			Find_mine(origin, show, x + 1, y + 1);
		if (x + 1 <=ROW&& y     > 0   && show[x + 1][y] == '*')//�·�
			Find_mine(origin, show, x + 1, y);
		if (x + 1 <=ROW&& y - 1 > 0   && show[x + 1][y - 1] == '*')//���·�
			Find_mine(origin, show, x + 1, y - 1);
		if (x     > 0  && y - 1 <=COL && show[x][y - 1] == '*')//��
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