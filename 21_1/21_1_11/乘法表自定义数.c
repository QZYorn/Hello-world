#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	int n;
	int i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= i; j++)
		{
			printf("%2d x%2d=%2d  ", i, j, i*j);
		}
		printf("\n");
	}
	return 0;
}