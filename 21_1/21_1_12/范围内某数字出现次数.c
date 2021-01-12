#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
int count_num(int i,int j,int obj)
{
	int count=0;
	for (; i < j; i++)
	{
		if (i / 10 == obj)
			count++;
		if (i % 10 == obj)
			count++;
	}
	return count;
}
int main()
{
	int count = count_num(1, 100, 9);
	printf("%d", count);
	return 0;
}