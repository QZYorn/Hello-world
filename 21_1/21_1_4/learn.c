#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
struct People
{
	char name[8];
	int age;
};
int main()
{
	struct People wang = {"王鸣飞",18};
	printf("名字：%s\n",wang.name);
	printf("年龄:%d\n",wang.age);
	wang.age = 16;
	printf("修订后年龄:%d\n", wang.age);
	return 0;
}