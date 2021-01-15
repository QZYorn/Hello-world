#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
void move_left(char arr[], int k)
{
	int sz=strlen(arr);
	int tmp1,tmp2;
	int i, j;
	for (i = 0; i < k; i++)
	{
		tmp1 = arr[0];//保存第一位
		for (j = 0; j < sz - 1; j++)//字符串向前挪一位
		{
			arr[j] = arr[j + 1];
		}
		arr[sz - 1] = tmp1;//把第一位放到最后一位
	}

}

int main()
{
	char arr[] = "abcde";
	int k;
	scanf("%d", &k);
	move_left(arr, k);
	printf("%s", arr);
	return 0;
}