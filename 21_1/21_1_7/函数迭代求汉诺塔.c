#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void HenNur(int i,char A,char B,char C)
{
	if (i == 1)
		printf("%c-->%c\n", A, C);
	else
	{
		HenNur(i - 1, A, C, B);
		printf("%c-->%c\n", A, C);
		HenNur(i - 1, B, A, C);
	}
}
int main()
{
	int i;
	scanf("%d", &i);
	HenNur(i,'A','B','C');
	return 0;
}