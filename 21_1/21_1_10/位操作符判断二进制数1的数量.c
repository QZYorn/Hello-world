#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int n,i,count;
	n = -1;
	count = 0;
	for (i = 0; i < 32; i++)
	{
		if ((n >> i & 1) == 1)
			count++;
	}
	printf("%d",count);
	return 0;
}