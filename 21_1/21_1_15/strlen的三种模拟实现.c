#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>
int My_strlen(const char* p)
{
	assert(p);
	/*int count = 0;
	while (*(p + count++));
	return count;*///计数器法

	/*if (!*p)
		return 1;
	return My_strlen(p + 1) + 1;*///递归法

	char* tmp = p;
	while (*tmp++);
	return tmp-p;//指针相减法
}
int main()
{
	char arr[] = "abcde";
	int len = My_strlen(arr);
	printf("%d", len);
	return 0;
}