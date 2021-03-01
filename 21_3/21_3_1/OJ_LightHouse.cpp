#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
#define N 4000001

struct Point
{
	long long x;
	long long y;
};

void merge()
{

}

void mergesort()
{

}

int main()
{
	
	int n;
	scanf("%d", &n);
	Point* poi = new Point[N];
	for (int i = 0; i < n; i++)
	{
		
		int x, y;
		scanf("%d %d", &x, &y);
		poi[i].x = x;
		poi[i].y = y;
	}

	return 0;
}