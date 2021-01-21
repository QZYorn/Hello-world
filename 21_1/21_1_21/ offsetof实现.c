#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#define OFFSETOF(name,mem) (int)&(((name*)0)->mem)
struct test
{
	int x;
	char y;
	short z;
};
int main()
{
	printf("%d", OFFSETOF(struct test,y));
	return 0;
}
