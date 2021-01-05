#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int n, k;
	int i=0;
	int j =1;
	for (n=1; n <= 10;n++)
	{

		for (j=1,k = 1; k <= n; k++)
		{
			j *= k;
			
		}
		i += j;
	}
	printf("%d", i);//Êä³ö1-10µÄ½×³ËºÍ
	
	return 0;
}