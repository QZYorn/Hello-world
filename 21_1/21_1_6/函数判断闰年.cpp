#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void run(int x)
{
	if (x % 400 == 0)
		printf("%d������", x);
	else if (x % 4 == 0 && x % 100 != 0)
		printf("%d������", x);
	else
		printf("%d��������", x);
}
int main()
{
	int year;
	scanf("%d", &year);
	run(year);
	return 0;
}