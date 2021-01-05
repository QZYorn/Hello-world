#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int i = 1;
	int key = 1;
	float sum = 0.0;
	for (i = 1; i <= 100; i++)
	{
		sum += key*1 / i;
		key = -key;
	}
	printf("%f\n", sum);
	return 0;
}