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
	printf("*********��Ϸ����*********\n");
	printf("*******��ӭ�´�����*******\n");
	printf("**************************\n");
	Sleep(1000);
}
void game()
{
	int rdm=rand()%100+1;
	int guess;
	system("cls");
	printf("**************************\n");
	printf("*****�������²¿���*******\n");
	printf("*******1��100֮���*******\n");
	printf("*******������ɶ�أ�*******\n");
	printf("**************************\n");
	Sleep(3000);
	system("cls");
ges:
	printf("������µ�����>");
	scanf("%d", &guess);
	if (guess > rdm)
	{
		printf("�´��ˣ�\n");
		goto ges;
	}
	else if(guess < rdm)
	{
		printf("��С�ˣ�\n");
		goto ges;
	}
	else
	{
		printf("����ˣ��𰸾���%d", rdm);
		Sleep(3000);
	}
}
void contin()
{
again:
	system("cls");
	printf("**************************\n");
	printf("******�Ƿ������Ϸ********\n");
	printf("*******1.������Ϸ*********\n");
	printf("*******2.�˳���Ϸ*********\n");
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
	printf("*******1.��ʼ��Ϸ*********\n");
	printf("*******2.�˳���Ϸ*********\n");
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