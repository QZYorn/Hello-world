#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
int compare(const void*x, const void*y)
{
	return (*(const float*)x) - (*(const float*)y);
}
int main()
{
	int i;
	float arr[] = { 9.0, 8.2, 6.4, 7.5, 4.5, 8.1, 2.5, 4.8 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	qsort(arr,sz,sizeof(float),compare);
	for (i = 0; i < sz; i++)
		printf("%.3f ", arr[i]);

	return 0;
}