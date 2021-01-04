#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void two()
{
	printf("two\n");
}
void one_three()
{
	printf("one\n");
	two();
	printf("three\n");
}
int main()
{
	printf("starting now:\n");
	one_three();
	printf("done!\n");
	return 0;
}