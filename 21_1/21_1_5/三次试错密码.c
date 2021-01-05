#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
int main()
{
	int i;
	char arr1[20] = {0};
	for (i = 0; i < 3;i++)
	{
		printf("ÇëÊäÈëÄúµÄÃÜÂë\n");
		scanf("%s",arr1);
		if (strcmp(arr1, "111111") == 0)
		{
			printf("ÃÜÂëÕýÈ·\n");
			break;
		}
		else
		{
			printf("ÃÜÂë´íÎó\n");
		}
	}
	if (i==3)
	{
		printf("ÍË³ö³ÌÐò");
	}
	return 0;
}