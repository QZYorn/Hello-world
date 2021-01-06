#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void ADD(int* p)
{
	(*p)++;
}
int main()
{
	int num=0;
	ADD(&num);
	ADD(&num);
	ADD(&num);
	ADD(&num);
	printf("%d\n",num);
	return 0;
}