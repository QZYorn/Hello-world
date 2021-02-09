#include<iostream>
using namespace std;

void FindMax(int A[], int lo, int hi,int &x1,int &x2)
{
	//递归基 <= 3
	if (lo + 3 >= hi)//1
	{
		if (A[x2 = lo] > A[x1 = lo + 1])//2
		{
			swap(x1, x2);
		}
		if (A[lo + 2] > A[x2])//2
		{
			if (A[x2 = lo + 2] > A[x1])//3
			{
				swap(x1, x2);
			}
		}
		return;
	}

	int mid = (lo + hi) >> 1;
	int x1L, x2L;
	FindMax(A, lo, mid, x1L, x2L);
	int x1R, x2R;
	FindMax(A, mid + 1, hi, x1R, x2R);

	if (A[x1L] > A[x1R])//1
	{
		x1 = x1L;
		x2 = (A[x2L] > A[x1R] ? x2L : x1R);//2
	}
	else//1
	{
		x1 = x1R;
		x2 = (A[x2R] > A[x1L] ? x2R : x1L);//2
	}
}

void Test01()
{
	int x1, x2;
	int A[] = { 18,1, 2, 3, 4, 5, 6, 7, 8, 9 ,15,13,11,10,15,16,2,5,8,1,9,5,7,5,2,8,21,4,8,15};
	FindMax(A, 0, sizeof(A) / sizeof(A[0]),x1,x2);
	cout << "最大值x1为：" << A[x1] << "  次大值x2为：" << A[x2];
}

int main()
{
	Test01();
	system("pause");
	return 0;
}