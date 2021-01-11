#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int My_string(char* arr)
{
	int count = 0;
	if (*arr != '\0')
		return (My_string(arr+1)+1);
	return 0;
}
void reverse_string(char* string)
{
	char* left = string;
	char* right = string + My_string(string)-1;
	char mid ;
	mid = *left;
	*left = *right;
	*right = '\0';
	if (My_string(string) > 3)
		reverse_string(string + 1);
	*right = mid;
}
int main()
{
	char arr[] = "123abcde2";
	int n;
	int i, j;
	reverse_string(arr);
	printf("%s", arr);
	return 0;
}