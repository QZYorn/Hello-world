#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#define MAX 16

bool work[MAX];//��λ
int curT[MAX][MAX];//����ʱ��
int minSum = 10000000;//��С�ܹ���ʱ��
int cSum;//��ǰ�ܹ���ʱ��
int n;//�������

void dfs(int cur)
{
	if (n <= cur)//�ݹ��
	{
		if (cSum < minSum)
		{
			minSum = cSum;
		}
		return;
	}

	for (int j = 0; j < n; ++j)
	{
		if (work[j] == false && cSum + curT[cur][j] < minSum)//��ǰ��λδ��ռ�� ���� ���ϵ�ǰ��ʱҲ��δ������С��ʱ��
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