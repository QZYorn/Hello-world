#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void Odd_Even(int arr[], int sz)
{
	int left = 0;
	int right = sz - 1;
	int mid;
	while (left < right)
	{
		while ((left < right) && (arr[left] % 2 == 1))
		{
			left++;
		}
		while ((left < right) && (arr[right] % 2 == 0))
		{
			right--;
		}
		if (left < right)
		{
			mid = arr[left];
			arr[left] = arr[right];
			arr[right] = mid;
		}
	}
}
	
void print(int arr[], int sz)
{
	int i;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
}
int main()
{
	int arr[] = { 2,1, 2, 3, 4, 5, 6, 7, 8, 9};
	int sz = sizeof(arr) / sizeof(arr[0]);
	Odd_Even(arr,sz);
	print(arr, sz);
	return 0;
}