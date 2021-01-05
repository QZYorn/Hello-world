#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int i ;
	int k ;
	int j =1;
	scanf("%d", &i);
	for ( k = 1; k <= i; k++)
	{
		j *= k;
	}
	printf("%d", j);
	//¼ÆËãnµÄ½×³Ë
	return 0;
}