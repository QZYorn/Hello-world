#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	int i, j;
	int mid,n;
	int count = 0;
	scanf("%d%d", &i, &j);
	mid = i^j;
	for (n = 0; n < 32; n++)
	{
		if (mid % 2 == 1)
		{
			count++;
		}
		mid = mid / 2;
	}
	printf("%d", count);
	return 0;
}