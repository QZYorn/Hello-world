#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
struct People
{
	char name[8];
	int age;
};
int main()
{
	struct People wang = {"������",18};
	printf("���֣�%s\n",wang.name);
	printf("����:%d\n",wang.age);
	wang.age = 16;
	printf("�޶�������:%d\n", wang.age);
	return 0;
}