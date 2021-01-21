#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#define ADD(x,y) ((x)+(y))
//#define PRINT(input,value) printf("the input is "input"\n",value)
#define PRINT(input,value) printf("the "#value" is "input"\n",value)
#define MERGE(name,num) name##num=num
#define MAX 10
int main()
{
	int ac, ca;
	int a=10;
	char c = 'i';
	PRINT("%c", c);
	PRINT("%d", c);
	PRINT("%d", MERGE(a,c));
	PRINT("%d", MERGE(c,a));

	return 0;
}