#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
void reverse(char* p1, char* p2)
{
	int tmp;
	while (p1 < p2)
	{
		tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}
void move_left(char arr[], int k)
{
	int sz=strlen(arr);
	reverse(arr, arr + k - 1);
	reverse(arr + k, arr + sz - 1);
	reverse(arr, arr + sz - 1);

}
void move_right(char arr[], int k)
{
	int sz = strlen(arr);
	reverse(arr+sz-k, arr +sz-1);
	reverse(arr , arr + sz - k-1);
	reverse(arr, arr + sz - 1);

}
int is_move_left(char arr1[], char arr2[])
{
	int k;
	int len = strlen(arr1);
	for (k = 0; k < len; k++)
	{
		move_left(arr1, 1);
		if (strcmp(arr1, arr2) == 0)
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	char arr1[] = "abcde";
	char arr2[] = "cdeab";
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