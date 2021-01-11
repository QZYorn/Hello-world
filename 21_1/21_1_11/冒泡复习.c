#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
void buble(int arr[],int sz)
{
	int i, j,mid,flag;
	for (i = 0; i < sz - 1; i++)
	{
		flag = 0;
		for (j = 0; j < sz - 1 - i; j++)
		{
			if (arr[j]>arr[j+1])
			{
				mid = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = mid;
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
	
}
int main()
{
	int arr[] = { 9, 8, 7, 6, 5, 4, 2, 3, 1 };
	int i = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);
	buble(arr,sz);
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}