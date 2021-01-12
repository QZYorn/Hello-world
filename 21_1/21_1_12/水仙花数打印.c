#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void Narcissistic_number(int i, int j)
{
	int x, y;
	int sum=0;
	for (; i < j; i++)
	{
		sum = 0;
		for (x=i;;x/=10)
		{
			sum += (x % 10)*(x % 10)*(x % 10);
			if (x < 10)
			{
				break;
			}
		}
		if (sum == i)
			printf("%d ", i);
	}
}
int main()
{
	int i, j;
	scanf("%d%d", &i, &j);
	Narcissistic_number(i, j);
	return 0;
}