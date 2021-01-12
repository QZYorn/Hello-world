#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int Sn(const int n)
{
	int sum=0;
	int mid=n;
	int i;
	for (i = 0; i < 5; i++)
	{
		sum += mid;
		mid=mid*10+n;
	}
	return sum;
}
int main()
{
	int i;
	scanf("%d", &i);
	printf("%d", Sn(i));
	return 0;
}