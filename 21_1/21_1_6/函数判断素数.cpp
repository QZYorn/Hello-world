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
	if (y>sqrt(x*1.0)&&x%2!=0||x==2)//�ų�XΪ2��2�ı������е�����
		printf("%d������", x);
	else
		printf("%d��������", x);
}
int main()
{
	int num;
	scanf("%d", &num);
	prime(num);
	return 0;
}