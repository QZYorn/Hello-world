#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void Odd_Even(int arr[], int sz)
{
	int left, right;
	int even_count = 0;
	int mid;
	for (left = 0; left < sz; left++)
	{
		if (arr[left] % 2 == 0)
			even_count++;
	}
	for (left = 0; left < sz - even_count; left++)
	{
		if (arr[left] % 2 == 0)
		{
			for (right = sz - 1; right>sz - even_count; right--)
			{
				if (arr[right] % 2 == 1)
				{
					mid = arr[left];
					arr[left] = arr[right];
					arr[right] = mid;
				}
			}
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
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,5,4,5 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	Odd_Even(arr,sz);
	print(arr, sz);
	return 0;
}