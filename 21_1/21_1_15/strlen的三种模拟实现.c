#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>
int My_strlen(const char* p)
{
	assert(p);
	/*int count = 0;
	while (*(p + count++));
	return count;*///��������

	/*if (!*p)
		return 1;
	return My_strlen(p + 1) + 1;*///�ݹ鷨

	char* tmp = p;
	while (*tmp++);
	return tmp-p;//ָ�������
}
int main()
{
	char arr[] = "abcde";
	int len = My_strlen(arr);
	printf("%d", len);
	return 0;
}