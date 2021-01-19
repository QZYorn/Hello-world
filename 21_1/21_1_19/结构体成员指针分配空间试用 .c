#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
typedef struct ST
{
	int a;
	int* b;
}ST;
int main()
{
	int i;
	ST* ps=(ST*)malloc(sizeof(ST));
	if (ps == NULL)
	{
		return 0;
	}
	ps->a = 100;
	ps->b = (int*)malloc(40);
	if (ps->b == NULL)
	{
		return 0;
	}
	for (i = 0; i < 5; i++)
	{
		ps->b[i] = i;
		printf("%d ",ps->b[i]);
	}
	free(ps->b);
	ps->b = NULL;
	free(ps);
	ps = NULL;
	return 0;
}