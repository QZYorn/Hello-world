#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 3;
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int q, s;
	scanf("%d", &q);
	s = sizeof(arr) / sizeof(arr[0]);
	while (arr[i] != q)//查找有序数组中具体某个数q
	{
		if (arr[i] < q)
			i = (i + s) / 2;
		else
			i = i / 2;
	}
	printf("arr[%d]", i);
	return 0;
}