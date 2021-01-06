#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void run(int x)
{
	if (x % 400 == 0)
		printf("%d是闰年", x);
	else if (x % 4 == 0 && x % 100 != 0)
		printf("%d是闰年", x);
	else
		printf("%d不是闰年", x);
}
int main()
{
	int year;
	scanf("%d", &year);
	run(year);
	return 0;
}