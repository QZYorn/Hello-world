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
		printf("�Ҳ���");
	}
	else
	{
		printf("�ҵ��ˣ��Ǳ���%d",i);
	}
	return 0;
}