#include<iostream>
using namespace std;

int Sum(int A[], int lo,int hi)
{
	if (lo < hi)
	{
		return Sum(A, lo, (lo + hi) >> 1) + Sum(A, ((lo + hi) >> 1) + 1, hi);
	}
	return A[lo];
	
}

void Test01()
{
	int A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	cout << Sum(A, 0 ,sizeof(A)/sizeof(A[0])-1);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}