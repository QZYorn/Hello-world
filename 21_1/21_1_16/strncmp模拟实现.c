#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
int My_strncmp(const char* str1, const char* str2,unsigned int n)
{
	assert(str1&&str2);
	while (*str2&&*str1&&--n)
	{
			str1++;
			str2++;
			if (*str1 != *str2)
				break;
	}
	if (*str1 == *str2&&!*str1)
		return 0;
	return *str1-*str2;
}
int main()
{
	char arr1[20] = "abbcaaa";
	char arr2[] = "abbc";
	int n = 100;
	printf("%d\n", My_strncmp(arr1, arr2,n));
	return 0;
}