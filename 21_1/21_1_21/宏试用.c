#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#define ADD(x,y) ((x)+(y))
#define MAX 10
int main()
{
	int i;
	int x=MAX;
	for (i = 0; i < 10; i++)
	{
		printf("x+i=%d\n", ADD(x, i));
		printf("file:%s   time:%s    date:%s  line:%d\n\n",__FILE__,__TIME__,__DATE__,__LINE__);
	}
	return 0;
}