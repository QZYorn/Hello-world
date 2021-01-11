#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
void Odd(int a)
{
	int i;
	int j = 0;
	printf(" Odd:");
	for (i = 30; i >= 0; i -= 2)
	{
		j = (a >> i)&1;
		printf("%d", j);
	}
	printf("\n");
}
void Even(int a)
{
	int i;
	int j = 0;
	printf("Even:");
	for (i = 31; i > 0; i -= 2)
	{
		j = (a >> i)&1;
		printf("%d", j);
	}
	printf("\n");
}
int main()
{
	int a;
	scanf("%d", &a);
	Odd(a);
	Even(a);
	return 0;
}