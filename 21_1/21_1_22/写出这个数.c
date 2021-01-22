#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int i;
	int sum = 0;
	char arr[100] = { 0 };
	char num[][5] = { "ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu" };
	scanf("%s", arr);
	for (i = 0;; i++)
	{
		if (arr[i] == 0)
			break;
		sum += arr[i] - '0';
	}
	if (sum>9)
	{
		if (sum>99)
		{
			i = sum / 100;
			printf("%s ", num[i]);
			sum -= 100 * i;
		}
		i = sum / 10;
		printf("%s ", num[i]);
		sum -= i * 10;
	}
	printf("%s", num[sum]);
	return 0;
}