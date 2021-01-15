#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int main()
{
	int a, b, c, d, e;
	int x;
	for (a = 1; a <= 5; a++)
	{
		for (b = 1; b <= 5; b++)
		{
			for (c = 1; c <= 5; c++)
			{
				for (d = 1; d <= 5; d++)
				{
					for (e = 1; e <= 5; e++)
					{
						if ((((b == 2) != (a == 3)) +
							 ((b == 2) != (e == 4)) +
							 ((c == 1) != (d == 2)) +
							 ((c == 5) != (d == 3)) +
							 ((e == 4) != (a == 1)) )== 5)
						{
							if (a*b*c*d*e == 120)//确保名次不重合
								printf("a=%d\nb=%d\nc=%d\nd=%d\ne=%d", a, b, c, d, e);
						}
					}
				}
			}
		}
	}
	return 0;
}