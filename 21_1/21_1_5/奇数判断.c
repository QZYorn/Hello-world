#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int main()
{
	int age;
	int i=1;
	while (i<100)
	{
		age = i % 2;
		
		if (1==age)
			printf("%d\n",i);
		i++;
	}
	return 0;
}