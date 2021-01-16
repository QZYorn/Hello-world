#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
void* My_memcpy(const void* dest, const void* src,unsigned int n)
{
	assert(dest&&src);
	void*tmp = dest;
	while (n--)
	{
		*((char*)dest)++ = *((char*)src)++;
	}
	return tmp;
}
int main()
{
	int  arr1[20] = {1,2,3,4,5,6,7};
	int arr2[] = {9,9,9};
	int i = 0;
	int n = 12;
	My_memcpy(arr1, arr2, n);
	for (i = 0; i < 20;i++)
	printf("%d\n", arr1[i]);
	return 0;
}