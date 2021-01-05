#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
int main()
{
	int i;
	int y=3;
	int count = 0;
	for (i = 101; i < 200; i+=2)
	{
		for (y = 3; y < sqrt(i);y+=2)
		{
				
			if (i%y==0)
			{

				break;
			}
		}
		if (y >= sqrt(i))
		printf("%d ", i);
		count++;
	}
	printf("\n共有%d个素数", count);
	return 0;
}