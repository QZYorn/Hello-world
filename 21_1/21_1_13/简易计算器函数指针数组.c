#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
int Add(int x, int y)
{
	return x + y;
}
int Sub(int x, int y)
{
	return x - y;
}
int Mul(int x, int y)
{
	return x * y;
}
int Div(int x, int y)
{
	return x / y;
}
void menu()
{
	printf("***************************\n");
	printf("****  1.Add     2.Sub  ****\n");
	printf("****  3.Mul     4.Div  ****\n");
	printf("*******    0.exit   *******\n");

}
void count(int(*p)(int, int))
{
	int x, y;
	printf("������Ҫ�������������>>");
	scanf("%d%d", &x, &y);
	printf("������Ϊ>>%d\n", p(x,y));

}
int main()
{
	int chio;
	int x, y;
	int(*parr[])(int, int) = {0, Add, Sub, Mul, Div };
	do
	{
		menu();
		printf("�˵�ѡ��>>");
		scanf("%d", &chio);
		if (chio <= 4 && chio >= 1)
			count(parr[chio]);
		else if (chio==0)
			printf("*******  ���˳�������  *******\n");
		else
			printf("�Ƿ�����");
	} while (chio);
	return 0;
}