#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
void* My_memmove(const void* dest, const void* src,unsigned int n)
{
	assert(dest&&src);
	void*tmp = dest;
	if (((char*)src - (char*)dest) > 0)
	{
		while (n--)
		{
			*((char*)dest)++ = *((char*)src)++;
		}
	}
	else
	{
		((char*)dest)+=n-1;
		((char*)src)+=n-1;
		while (n--)
		{
			
			*((char*)dest)-- = *((char*)src)--;
		}
	}
	return tmp;
}
int main()
{
	int  arr1[] = {1,2,3,4,5,6,7};
	int arr2[] = {9,9,9};
	int i = 0;
	int n = 12;
	My_memmove(arr1+2, arr1, n);
	for (i = 0; i < 7;i++)
	printf("%d ", arr1[i]);
	return 0;
}