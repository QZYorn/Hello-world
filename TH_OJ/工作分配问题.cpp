#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#define MAX 16

bool work[MAX];//工位
int curT[MAX][MAX];//工作时长
int minSum = 10000000;//最小总工作时长
int cSum;//当前总工作时长
int n;//最大人数

void dfs(int cur)
{
	if (n <= cur)//递归基
	{
		if (cSum < minSum)
		{
			minSum = cSum;
		}
		return;
	}

	for (int j = 0; j < n; ++j)
	{
		if (work[j] == false && cSum + curT[cur][j] < minSum)//当前工位未被占用 并且 加上当前耗时也仍未超出最小总时间
		{
			work[j] = true;
			cSum += curT[cur][j];
			dfs(cur + 1);
			work[j] = false;
			cSum -= curT[cur][j];
		}
	}
	
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> curT[i][j];
		}
	}
	dfs(0);
	cout << minSum;
	return 0;
}