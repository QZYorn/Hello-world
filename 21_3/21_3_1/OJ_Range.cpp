#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<time.h>
using namespace std;

int binSearch(int* &arr ,int a,int b,int x)
{
	while (a < b)
	{
		int mid = (a + b) >> 1;
		x < arr[mid] ? b = mid : a = mid + 1;
	}
	return --a;
}

int partition(int* &arr, int lo, int hi)
{
	swap(arr[lo], arr[rand() % (hi - lo) + lo]);
	int pivot = arr[lo];
	while (lo < hi)
	{
		while (lo < hi && pivot <= arr[hi])
		{
			hi--;
		}
		arr[lo] = arr[hi];
		while (lo < hi && arr[lo] <= pivot)
		{
			lo++;
		}
		arr[hi] = arr[lo];
	}
	arr[lo] = pivot;
	return lo;
}

void sort(int* &arr, int lo, int hi)
{
	/*while (size != 0)
	{
		int last = hi;
		hi = 0;
		for (int j = 0; j < last; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				hi = j;
			}
		}
	}*/
	
	if (hi - lo < 2)
		return;
	int mi = partition(arr,lo, hi);
	sort(arr, lo    , mi);
	sort(arr, mi + 1, hi);
}

int main()
{
	srand((unsigned int) time(NULL));
	//点的个数n，查询次数m
	int n, m;
	//INT_MAX;
	scanf("%d %d", &n, &m);
	int iosize = 1 << 20;
	int arsize = 10000002;
	int * arr = new int[arsize];
	memset(arr, 0x3f, arsize);
	arr[0] = -1;//左标志
	
	for (int i = 1; i < n + 1; i++)
	{
		scanf("%d", &arr[i]);
	}
	sort(arr, 1, n + 1);
	//测试
	/*for (int i = 0; i < n + 1; i++)
	{
		cout << arr[i] << " ";
	}*/
	setvbuf(stdin , new char[iosize], _IOFBF, iosize);
	setvbuf(stdout, new char[iosize], _IOFBF, iosize);

	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		int aa = binSearch(arr, 1 , n + 1, a);//arr[aa] <=a
		int bb = binSearch(arr, aa-1, n + 1, b);
		
		int count = 0;

		/*if (arr[aa] == a || arr[bb] == b)
		{
			count++;
			if (arr[aa] == a && arr[bb] == b)
			{
				count++;
			}
		}*/
		if (arr[aa] == a)
		{
			count++;
		}
		count += bb - aa;
		printf("%d\n", count);
	}
	return 0;
}