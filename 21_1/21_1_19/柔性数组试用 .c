#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
struct STU
{
	int a;
	int b[];
};
int main()
{
	int i;
	struct STU *ps = (struct STU*)malloc(sizeof(struct STU) + 5 * sizeof(int));
	if (ps == NULL)
	{
		return 0;
	}
	for (i = 0; i < 5; i++)
	{
		ps->b[i] = i;
	}
	for (i = 0; i < 5; i++)
	{
		printf("%d ", ps->b[i]);
	}
	struct STU *p2 = (struct STU*)realloc(ps, 44);
	if (p2 != NULL)
	{
		ps = p2;
	}
	for (i = 0; i < 10; i++)
	{
		printf("%d ", ps->b[i]);
	}
	free(ps);
	ps = NULL;
	return 0;
}