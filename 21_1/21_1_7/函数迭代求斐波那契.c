#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int Fib(int x)
{
	int a = 1;
	int b = 1;
	int c = 1;
	while (x > 2)
	{
		b = a;
		a = c;
		c = a + b;
		x--;
	}
	return c;
}
int main()
{
	int i;
	scanf("%d", &i);
	printf("%d\n", Fib(i));
	return 0;
}