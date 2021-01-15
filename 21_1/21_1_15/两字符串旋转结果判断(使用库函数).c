#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
int is_move_left(char arr1[], char arr2[])
{
	int k;
	int len1 = strlen(arr1);
	int len2 = strlen(arr2);
	if (len1 != len2)
		return 0;
	strncat(arr1, arr1, len1);
	if (strstr(arr1, arr2)!=NULL)
	{
		return 1;
	}
	return 0;
}
int main()
{
	char arr1[20] = "abcde";
	char arr2[] = "cddab";
	int k=2;
	if (is_move_left(arr1, arr2) == 1)
	{
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}
	return 0;
}