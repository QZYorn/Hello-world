#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
char* My_strncpy(char* dest, const char* str,unsigned int n)
{
	assert(dest&&str);
	char* tmp = dest;
	while (n--)
	{
		if (*str)
		*dest++ = *str++;
		else
			*dest++ = '\0';
	}

	return tmp;
}
int main()
{
	char arr1[20] = "aaaaaaaaaa";
	char arr2[] = "cccc";
	int n = 7;
	//strcat(arr1, arr2);
	printf("%s\n", My_strncpy(arr1, arr2,n));
	return 0;
}