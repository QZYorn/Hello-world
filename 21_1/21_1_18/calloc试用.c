#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int i;
	int input;
	scanf("%d", &input);
	int* p = (int*)calloc(input, sizeof(int));
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		for (i = 0; i < input; i++)
			printf("%d ", *(p + i));
	}
	free(p);
	p = NULL;
	return 0;
}