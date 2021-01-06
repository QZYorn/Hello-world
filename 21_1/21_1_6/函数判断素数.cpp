#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
void prime(int x)
{
	int y = 0;
	for (y = 3; y < sqrt(x*1.0); y += 2)
	{
		if (x%y == 0)
			break;
	}
	if (y>sqrt(x*1.0)&&x%2!=0||x==2)//排除X为2或2的倍数误判的现象
		printf("%d是素数", x);
	else
		printf("%d不是素数", x);
}
int main()
{
	int num;
	scanf("%d", &num);
	prime(num);
	return 0;
}