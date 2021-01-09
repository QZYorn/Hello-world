#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void Bubble(int arr1[], int sz)
{
	int i, j,k;
	int flag;
	for (j = 0; j < sz; j++)
	{
		flag = 0;
		for (i = 0; i < sz - 1 - j; i++)
		{
			if (arr1[i]>arr1[i + 1])
			{
				k = arr1[i];
				arr1[i] = arr1[i + 1];
				arr1[i + 1] = k;
				flag = 1;

			}
		}
		if (flag == 0)
			break;
	}
}
int main()
{
	int arr1[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	int sz = sizeof(arr1) / sizeof(arr1[0]);
	int i;
	Bubble(arr1, sz);
	for (i = 0; i < sz;i++)
	{
		printf("%d ", arr1[i]);
	}
	return 0;
}