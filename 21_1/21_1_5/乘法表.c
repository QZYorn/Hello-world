#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int x = 1;
	int y = 1;
	int product = 0;
	for (y = 1; y < 10; y++)
	{
		for (x = 1; x <= y; x++)
		{
			product = x*y;
			printf("  %dx%d=%d  ", y, x, product);
			if (product < 10)
			printf(" ");
		}
		printf("\n");
	}
	return 0;
}