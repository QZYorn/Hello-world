#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
char* My_strstr(const char* str1, const char* str2)
{
	assert(str1&&str2);
	char* tmp = (char*)str1;
	char *p1 ,*p2;
	if (!*str2)
		return tmp;
	while (*tmp)
	{
		p1 = tmp;
		p2 = (char*)str2;
		while (*p1 == *p2)
		{
			p1++;
			p2++;
			if (!*p2)
				return tmp;
		}
		tmp++;
	}
	return NULL;
}
int main()
{
	char arr1[20] = "abbbcaaa";
	char arr2[] = "";
	int n = 100;
	printf("%s\n", My_strstr(arr1, arr2));
	return 0;
}