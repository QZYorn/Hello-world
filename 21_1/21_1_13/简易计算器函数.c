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
int main()
{
	int chio;
	int x, y;
	do
	{
		menu();
		printf("菜单选择>>");
		scanf("%d", &chio);
		if (chio != 0)
		{
			printf("请输入要计算的两个数字>>");
			scanf("%d%d",&x, &y);
		}
		switch (chio)
		{
		case 1:
			printf("计算结果为>>%d\n", Add(x,y));
			break;
		case 2:
			printf("计算结果为>>%d\n", Sub(x,y));
			break; 
		case 3:
			printf("计算结果为>>%d\n", Mul (x, y));
			break;
		case 4:
			printf("计算结果为>>%d\n", Div(x, y));
			break;
		case 0:
			printf("*******  已退出计算器  *******\n");
			break;
		default:
			printf("非法输入");
			break;
		}
	} while (chio);
	return 0;
}