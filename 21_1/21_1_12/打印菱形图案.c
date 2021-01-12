#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void primtic(int n)
{
	int i,j;

	for (i = 0; i < n; i++)
	{
		for (j = i; j < n; j++)
		{
			printf(" ");
		}
		for (j = 0; j < 2 * i + 1; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	for (i = n; i >= 0; i--)
	{
		for (j = i; j < n; j++)
		{
			printf(" ");
		}
		for (j = 0; j < 2 * i + 1; j++)
		{
			printf("*");
		}
		printf("\n");
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	primtic(n);
	return 0;
}