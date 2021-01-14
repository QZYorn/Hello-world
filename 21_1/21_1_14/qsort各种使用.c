#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Stu
{
	char name[10];
	int age;
	float score;
};


int cmp_int(const void*x, const void*y)
{
	return (*(const int*)x) - (*(const int*)y);
}
int cmp_float(const void*x, const void*y)
{
	return (*(const float*)x) - (*(const float*)y);
}


int cmp_Stu_name(const void*x, const void*y)
{
	return strcmp((((const struct Stu*)x)->name),(((const struct Stu*)y)->name));
}
int cmp_Stu_age(const void*x, const void*y)
{
	return (((const struct Stu*)x)->age) - (((const struct Stu*)y)->age);
}
int cmp_Stu_score(const void*x, const void*y)
{
	return (((const struct Stu*)x)->score) - (((const struct Stu*)y)->score);
}

int main()
{
	void qsort(void *base, size_t nitems, size_t size, int(*compar)(const void *, const void*));
	int arr1[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	float arr2[] = { 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };
	struct Stu St3[4] = { {"zhangsan",18,97.0}, {"lisi",21,99.0}, {"wangwu",16,66.6}, {"daliu",22,88.8} };

	int sz1 = sizeof(arr1) / sizeof(arr1[0]);
	int sz2 = sizeof(arr2) / sizeof(arr2[0]);

	qsort(arr1, sz1, sizeof(int), cmp_int);
	qsort(arr2, sz2, sizeof(float), cmp_float);

	qsort(St3, 4, sizeof(struct Stu), cmp_Stu_age);
	qsort(St3, 4, sizeof(struct Stu), cmp_Stu_score);
	qsort(St3, 4, sizeof(struct Stu), cmp_Stu_name);

	return 0;
}