#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int which_endian()
{
	union UN
	{
		int a;
		char b;
	};
	union UN x;
	x.a = 1;
	if (x.a == x.b)
		return 0;
	else
		return 1;
}
int main()
{
	if (which_endian() == 1)
		printf("��˴洢");
	else
		printf("С�˴洢");
	return 0;
}