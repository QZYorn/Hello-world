#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int search(int x,int arr[],int sz)
{
	int left, right,mid;
	right = sz-1;
	left = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (arr[mid] < x)
		{
			left = mid+1;
		}
		else if (x < arr[mid])
		{
			right = mid-1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}
int main()
{
	int num,i,sz;
	int arr[] = {1,2,3,4,5,6,7,8,9};
	sz = sizeof(arr) / sizeof(0);
	scanf("%d", &num);
	i=search(num,arr,sz);
	if (i == -1)
	{
		printf("找不到");
	}
	else
	{
		printf("找到了，角标是%d",i);
	}
	return 0;
}