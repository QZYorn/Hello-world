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
	printf("请输入要计算的两个数字>>");
	scanf("%d%d", &x, &y);
	printf("计算结果为>>%d\n", p(x,y));

}
int main()
{
	int chio;
	int x, y;
	int(*parr[])(int, int) = {0, Add, Sub, Mul, Div };
	do
	{
		menu();
		printf("菜单选择>>");
		scanf("%d", &chio);
		if (chio <= 4 && chio >= 1)
			count(parr[chio]);
		else if (chio==0)
			printf("*******  已退出计算器  *******\n");
		else
			printf("非法输入");
	} while (chio);
	return 0;
}