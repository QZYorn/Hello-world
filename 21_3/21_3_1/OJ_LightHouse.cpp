#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
#define N 4000010


struct Point
{
	long long x;
	long long y;
	void operator=(Point &str)
	{
		x = str.x;
		y = str.y;
	}
};

Point* B = new Point[2000005];

void merge(Point* &poi,int lo, int mi, int hi)
{
	int la = lo;
	Point* A = poi + lo;
	int lb = mi - lo;//[lo,mi)
	for (int i = 0; i < lb; i++)
	{
		B[i] = A[i];
	}
	int lc = hi - mi;//[mi,hi)
	Point* C = poi + mi;
	for (int i = 0, j = 0, k = 0;j < lb;)//B�Ⱥľ��ͽ���
	{
		if ((lc <= k) || (B[j].x <= C[k].x))//B<=C ���� C�Ⱥľ�
			A[i++] = B[j++];
		else
			A[i++] = C[k++];
	}
}

long long inversion(Point* &poi, int lo, int mi, int hi)
{
	long long inv = 0;

	int la = lo;
	Point* A = poi + lo;
	int lb = mi - lo;//[lo,mi)
	for (int i = 0; i < lb; i++)
	{
		B[i].y = A[i].y;
	}
	int lc = hi - mi;//[mi,hi)
	Point* C = poi + mi;
	for (int i = 0, j = 0, k = 0; j < lb;)//B�Ⱥľ��ͽ���
	{
		if ((lc <= k) || (B[j].y <= C[k].y))//B<=C ���� C�Ⱥľ�
		{
			A[i++].y = B[j++].y;
			if (k < lc)
			{
				inv += lc - k;
			}
		}
		
		else
		{
			A[i++].y = C[k++].y;
			//inv += lb - j;
		}
			
	}
	return inv;
}

long long mergesort(Point* &poi, int lo,  int hi,const bool flag)//��ʱ������x����ʱ������y�ַ�������Ը���
{
	if (hi - lo < 2)
	{
		//if (flag && (poi[lo].y > poi[hi].y))
		//	return 1;
		return 0;
	}
	int mi = (lo + hi) >> 1;
	
	if (flag)
	{
		long long inv = mergesort(poi, lo, mi, flag);
		    inv+= mergesort(poi, mi, hi, flag);
		    inv+= inversion(poi, lo, mi, hi);

		return inv;
	}
		
	else
	{
		mergesort(poi, lo, mi, flag);
		mergesort(poi, mi, hi, flag);
		merge(poi, lo, mi, hi);

		return 0;
	}
		
}

int main()
{

	int n;
	scanf("%d", &n);
	Point* poi = new Point[N];
	for (int i = 0; i < n; i++)
	{
		//int x, y;
		scanf("%d %d", &poi[i].x, &poi[i].y);
		/* = x;
		 = y;*/
	}
	
	//����x
	mergesort(poi, 0, n, false);
	//Ȼ����y�����������
	long long inv = mergesort(poi, 0, n, true);

	//long long num = n*(n - 1) / 2 - inv;
	printf("%lld\n", inv);
	return 0;
}