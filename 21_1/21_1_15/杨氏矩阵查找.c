#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int is_live(int arr[3][3], int* row, int* col, int k)
{
	int x = 0;
	int y = *col-1;
	while ((x<=*row-1)&&(y>=0))
	{
		if (arr[x][y] < k)
		{
			x++;
		}
		else if (arr[x][y]>k)
		{
			y--;
		}
		else
		{
			*row = x;
			*col = y;
			return 1;
		}
	}
	return 0;
}
int main()
{
	int arr[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
	int k = 9;
	int x = 3;
	int y = 3;
	if (is_live(arr, &x,&y, k) == 1)
	{
		printf("找到了\n");
		printf("角标是%d %d\n",x,y);

	}
	else
	{
		printf("没找到\n");
	}
	return 0;
}