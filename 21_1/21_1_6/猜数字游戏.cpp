#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
int sle;
void exit()
{
	system("cls");
	printf("**************************\n");
	printf("*********游戏结束*********\n");
	printf("*******欢迎下次再来*******\n");
	printf("**************************\n");
	Sleep(1000);
}
void game()
{
	int rdm=rand()%100+1;
	int guess;
	system("cls");
	printf("**************************\n");
	printf("*****萨，来猜猜看吧*******\n");
	printf("*******1至100之间喔*******\n");
	printf("*******数字是啥呢？*******\n");
	printf("**************************\n");
	Sleep(3000);
	system("cls");
ges:
	printf("输入你猜的数字>");
	scanf("%d", &guess);
	if (guess > rdm)
	{
		printf("猜大了！\n");
		goto ges;
	}
	else if(guess < rdm)
	{
		printf("猜小了！\n");
		goto ges;
	}
	else
	{
		printf("答对了！答案就是%d", rdm);
		Sleep(3000);
	}
}
void contin()
{
again:
	system("cls");
	printf("**************************\n");
	printf("******是否继续游戏********\n");
	printf("*******1.继续游戏*********\n");
	printf("*******2.退出游戏*********\n");
	printf("**************************\n");
	scanf("%d",&sle);
	switch (sle)
	{
	case 1:
		game();
		contin();
		break;
	case 2:
		exit();
		break;
	default:
		goto again;
	}
}

int main()
{
	
	srand((unsigned int)time(NULL));
again:
	system("cls");
	printf("**************************\n");
	printf("*******1.开始游戏*********\n");
	printf("*******2.退出游戏*********\n");
	printf("**************************\n");
	scanf("%d",&sle);
	switch (sle)
	{
		case 1:
			game();
			contin();
			break;
		case 2:
			exit();
			break;
		default:
			goto again;
	}
	return 0;
}