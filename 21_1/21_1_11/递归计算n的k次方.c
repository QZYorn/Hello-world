#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
float Exp(int n,int k)
{
	if (k < 0)
		return 1.0/n*Exp(n,(k+1));
	else if (k == 0)
		return 1;
	else
		return n*Exp(n, k - 1);
}
int main()
{
	int n;
	int k;
	scanf("%d%d", &n,&k);
	printf("Exp=%f",Exp(n,k));
	return 0;
}