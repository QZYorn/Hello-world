#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
char* My_strcat(char* dest, const char* str)
{
	assert(dest&&str);
	char* tmp = dest;
	while (*dest++);
	dest--;
	while (*dest++ = *str++);
	return tmp;
}
int main()
{
	char arr1[20] = "abcde";
	char arr2[] = "cdehg";
	//strcat(arr1, arr2);
	printf("%s\n", My_strcat(arr1, arr2));
	return 0;
}