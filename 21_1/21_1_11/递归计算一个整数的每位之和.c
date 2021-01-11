#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int DigitSum(int n)
{
	int i = n / 10;
	if (i < 1)
		return n % 10;
	return (DigitSum(i) + n % 10);
}
int main()
{
	int n;
	scanf("%d", &n);
	printf("%d",DigitSum(n));
	return 0;
}