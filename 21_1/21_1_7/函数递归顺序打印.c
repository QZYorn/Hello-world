#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void print(int i)
{
	if (i > 10)
	{
		 print(i / 10);
	}
		printf("%d ", i % 10);
}
int main()
{
	int i;
	scanf("%d", &i);
	print(i);
	return 0;
}