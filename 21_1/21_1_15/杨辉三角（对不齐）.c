#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int main()
{
	int arr[10][10] = { 0 };
	int i, j;
	int szi = sizeof(arr) / sizeof(arr[0]);
	int szj = sizeof(*arr) / sizeof(arr[0][0]);
	for (i = 0; i < szi; i++)
	{
		for (j = 0; j < szj; j++)
		{
			if (j == 0)//数组赋值
			{
				arr[i][j] = 1;
			}
			else if (j == i)
			{
				arr[i][j] = 1;
			}
			else
			{
				arr[i][j] = arr[i-1][j-1]+arr[i-1][j]; 
			}
		}
	}
	for (i = 0; i < szi; i++)
	{
		for (j = 0; j < szi-i; j++)
		{
			printf("  ");
		}
		for (j = 0; j < szj; j++)
		{
			if (j<=i)//打印数组
			printf("%-3d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}