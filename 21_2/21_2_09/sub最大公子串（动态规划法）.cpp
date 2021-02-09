#include<iostream>
using namespace std;
#include<vector>

int FindMaxSub(char A[], char B[],int Al,int Bl)
{
	int length = 0;
	vector<vector<int>> v;
	for (int i = 0; i <= Al; i++)//创建二维向量,Al+1行，Bl+1列
	{
		vector<int> vtmp;
		vtmp.resize(Bl+1, 0);
		v.push_back(vtmp);
	}

	for (int i = 1; i <= Al; i++)
	{
		for (int j = 1; j <= Bl; j++)
		{
			int max;
			int   up = v[i - 1][j];//上一格
			int left = v[i][j - 1];//左一格
			max = ( left> up ? left : up);//取较大者
			if (A[i - 1] == B[j - 1])
			{
				v[i][j] = v[i-1][j-1] + 1;
			}
			else
			{
				v[i][j] = max;
			}
		}
	}
	return v[Al][Bl];
}

void Test01()
{
	char A[] = "abcdefg";
	char B[] = "eeeagggbjjjceee";
	int length = FindMaxSub(A, B, sizeof(A)-1, sizeof(B)-1);
	cout << "最大子串长度为为：" << length << endl;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}