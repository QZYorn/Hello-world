#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
int My_strcmp(const char* dest, const char* str)
{
	assert(dest&&str);
	while (*dest++ == *str++)
	{
		if (!*dest)
			return 0;
	}
	return (*(--(unsigned char*)dest)-*(--(unsigned char*)str));
}
int main()
{
	char arr1[20] = "abcdeaaa";
	char arr2[] = "abcde";
	//strcat(arr1, arr2);
	printf("%d\n", My_strcmp(arr1, arr2));
	return 0;
}