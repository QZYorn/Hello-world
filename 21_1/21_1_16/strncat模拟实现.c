#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
char* My_strncat(char* dest, const char* str,unsigned int n)
{
	assert(dest&&str);
	char* tmp = dest;
	while (*dest++);
	dest--;
	while ((n--)&&(*str))
	{
		*dest++ = *str++;
	}
	*dest = '\0';
	return tmp;
}
int main()
{
	char arr1[20] = "abcde";
	char arr2[] = "cccc";
	int n = 7;
	printf("%s\n", My_strncat(arr1, arr1,n));
	return 0;
}