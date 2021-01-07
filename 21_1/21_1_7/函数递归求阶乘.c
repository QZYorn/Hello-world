#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int Facl(int x)
{
	if (x > 0)
	{
		return Facl(x-1)*x;
	}
	else
	{
		return 1;
	}
}
int main()
{
	int i;
	scanf("%d", &i);
	printf("%d\n", Facl(i));
	return 0;
}