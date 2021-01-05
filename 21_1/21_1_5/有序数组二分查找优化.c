#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 10 };
	int q, sz;
	int left, right,mid;
	scanf("%d", &q);
	sz = sizeof(arr) / sizeof(arr[0]);
	left = 0;
	right = sz;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (q < arr[mid])
		{
			right = mid - 1;
		}
		else if (q>arr[mid])

		{
			left = mid + 1;
		}
		else
		{
			printf("脚标是%d\n", mid);
			break;
		}
	}
	if (left>right)
	{
		printf("找不到\n");
	}
	return 0;
}