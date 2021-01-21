#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

#define ADD(x,y) ((x)+(y))
#ifndef __FLAG__
#define __FLAG__
#define PRINT(input,value) printf("the input is "input"\n",value)
#endif
#ifndef __FLAG__
#define __FLAG__
#define PRINT(input,value) printf("the "#value" is "input"\n",value)
#endif
#define MERGE(name,num) name##num=num
#define __DEBUG__ 1
#define MAX 10
int main()
{
	int ac, ca;
	int a=10;
	char c = 'i';
#ifdef MERGE
	#if defined(ADD)
		PRINT("%c", c);
	#endif
	#ifndef PRINT
		PRINT("%d", c);
	#endif
	#if(__DEBUG__)
		PRINT("%d", MERGE(a,c));
	#elif(!__DEBUG__)
		PRINT("%d", MERGE(c,a));
	#endif
#endif
	return 0;
}