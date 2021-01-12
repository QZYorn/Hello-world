#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
void swap(int* p1,int* p2,int sz)
{
	int mid,i;
	assert(p1 != NULL&&p2 != NULL);
	for (i = 0; i < sz - 1; i++)
	{
		mid = *p1;
		*p1 = *p2;
		*p2 = mid;
		p1++;
		p2++;
	}
}
int main()
{
	int arr1[] = { 1, 2, 3 };
	int arr2[] = { 9, 8, 7 };
	int sz = sizeof(arr1) / sizeof(arr1[0]);
	swap(arr1, arr2,sz);
	printf("%d ", arr1[0]);
	return 0;
}