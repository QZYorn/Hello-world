#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int arr[16][16];
	memset(arr, '\0', sizeof(arr));
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	}
	for (int j = 0; j < n; j++)
	{
		for (int i = j; i < n; i++)
		{
			bool is_sort = true;
			for (int k = j; k < n - 1; k++)
			{
				if (arr[k][j] > arr[k + 1][j])
				{
					swap(arr[k], arr[k + 1]);
					is_sort = false;
				}
			}
			if (is_sort)
				break;
		}
	}
	for (int i = 0; i < n; i++)
	{
		sum += arr[i][i];
	}
	/*for (int j = 0; j < n; j++)
	{
		int min = 10001;
		for (int i = 0; i < n; i++)
		{
			if (arr[i][j] < min)
			{
				min = arr[i][j];
			}
			
		}
		sum += min;
	}*/
	cout << sum;
	return 0;
}