#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
void game()
{
	char origin[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };

	initboard(origin,  '0');//里雷盘 初始化
	initboard(show,  '*');//表雷盘 初始化
	//revealboard(origin);//显示 里雷盘
	revealboard(show);//显示 表雷盘
	lay_mine(origin, MINES);//埋雷
	//revealboard(origin);//显示 里雷盘
	clear_mine(origin,show);
}
void game_exit()
{
	printf("****感谢您的游玩!*****\n");
}
int main()
{
	int choose;
	srand((unsigned int)time(NULL));
first:
	printf("**********************\n");
	printf("*****欢迎来到扫雷*****\n");
	printf("******1.开始游戏******\n");
	printf("******2.退出游戏******\n");
	printf("**********************\n");
again:
	printf("请输入>");
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