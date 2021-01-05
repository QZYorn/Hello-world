#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int a, b;
	int c = 1;
	scanf("%d%d",&a,&b);
	if (a < b)
	{
		a += b;
		b = a-b;
		a = b - a;
	}//较大数置于前
	
	while (c!=0)
	{
		c = a%b;
		a = b;
		b = c;
	}
	if (c == 0)
	{
		printf("最大公约数是%d\n",a);
	}
	return 0;
}