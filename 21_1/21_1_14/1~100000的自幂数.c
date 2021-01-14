#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int My_count(int i)
{
	int count = 1;
	while (i >= 10)
	{
		i /= 10;
		count++;
	}
	return count++;
}
int pow(int a, int n)
{
	int sum=a;
	for (; n > 1; n--)
	{
		sum=sum*a;
	}
	return sum;
}
int main()
{
	int i, j,a;
	int sum = 0;
	int count = 0;
	for (i = 0; i < 100000; i++)
	{
		sum = 0;
		count = My_count(i);
		for (j=i; j > 0; j /= 10)
		{
			a = j % 10;
			sum += pow(a,count);
		}
		if (sum == i||i==0)
		{
			printf("%d ", i);
		}

	}
	return 0;
}