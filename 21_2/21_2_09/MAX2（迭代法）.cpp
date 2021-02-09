#include<iostream>
using namespace std;

void FindMax(const int A[], int lo, int hi,int &x1,int &x2)
{
	//初始化
	x1 = A[lo];
	x2 = A[lo + 1];
	if (x1 < x2)
		swap(x1, x2);

	for (int i = 0; i < hi; i++)//遍历数组
	{
		if (A[i] > x2)
		{
			x2 = A[i];
			if (x1 < x2)
				swap(x1, x2);
		}
	}


}

void Test01()
{
	int x1, x2;
	int A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 ,15,13,11,10,15,16,2,5,8,1,9,5,7,5,2,8,21,4,8,15};
	FindMax(A, 0, sizeof(A) / sizeof(A[0]),x1,x2);
	cout << "最大值x1为：" << x1 << "  次大值x2为：" << x2 << endl;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}