#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
using namespace std;
#define MAX 51
int f[MAX][MAX][MAX];
int arr[MAX][MAX];

int max(int i, int j, int k, int l)
{
	if (i < j) i = j;
	if (i < k) i = k;
	if (i < l) i = l;
	return i;
}

int main()
{
	int m = 0;
	int n = 0;
	cin >> m >> n;
	for (int i = 1; i <= m; ++i)
	for (int j = 1; j <= n; ++j)
		cin >> arr[i][j];
	for (int i = 1; i <= m; ++i)
	for (int j = 1; j <= n; ++j)
	for (int k = 1; k <= m; ++k)
	{
		f[i][j][k] = max(f[i - 1][j][k - 1], f[i - 1][j][k],
						 f[i][j - 1][k - 1], f[i][j - 1][k]);
		if (i == k)
			f[i][j][k] += arr[i][j];
		else
			f[i][j][k] += arr[i][j] + arr[k][i + j - k];
	}
	cout << f[m][n][m];
}

