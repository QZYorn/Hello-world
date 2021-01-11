#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
void init(int* p, int sz)
{
	int i;
	for (i = 0; i < sz; i++)
	{
		*(p + i) = 0;
	}
}
void print(int*p, int sz)
{
	int i;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", *(p + i));
	}
}
void reverse(int arr[], int begin,int end)
{
	int mid;
	if (end-begin <= 1)
		return;
	mid = arr[begin];
	arr[begin] = arr[end];
	arr[end] = mid;
	reverse(arr, begin+1,end-1);
}
int main()
{
	int arr[10] = { 1,2,3,4,5,6,7,8,9,0 };
	int i = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);
	//init(arr, sz);//初始化数组为全0
	print(arr,sz);//打印数组每个元素
	printf("\n");
	reverse(arr, 0,sz-1);//逆置数组元素
	print(arr, sz);
		return 0;
}