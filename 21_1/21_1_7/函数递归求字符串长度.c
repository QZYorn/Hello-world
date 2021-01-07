#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int str(char* i)
{
	if (*i != '\0')
	{
		return 1 + str(i+1);
	}
	else
	{
		return 0;
	}
}
int main()
{
	char arr[] = "tes12312121t";
	printf("%d\n", str(arr));
	return 0;
}