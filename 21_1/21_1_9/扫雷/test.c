#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
void game()
{
	char origin[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };

	initboard(origin,  '0');//������ ��ʼ��
	initboard(show,  '*');//������ ��ʼ��
	//revealboard(origin);//��ʾ ������
	revealboard(show);//��ʾ ������
	lay_mine(origin, MINES);//����
	//revealboard(origin);//��ʾ ������
	clear_mine(origin,show);
}
void game_exit()
{
	printf("****��л��������!*****\n");
}
int main()
{
	int choose;
	srand((unsigned int)time(NULL));
first:
	printf("**********************\n");
	printf("*****��ӭ����ɨ��*****\n");
	printf("******1.��ʼ��Ϸ******\n");
	printf("******2.�˳���Ϸ******\n");
	printf("**********************\n");
again:
	printf("������>");
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:
		game();
goto first;
		break;
	case 2:
		game_exit();
		break;
	default:
		goto again;
		break;
	}
	return 0;
}