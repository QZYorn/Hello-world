#include<iostream>
using namespace std;

void ArrSwap(int *A, int lo, int hi)
{
	if (lo < hi)
	{
		swap(A[lo], A[hi]);
		ArrSwap(A, lo+1,hi-1);
	}
	else if (lo > hi)//µÝ¹é»ù
	{

	}
	else if (lo == hi)
	{
		
	}
	
}

void Test01()
{
	int A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ArrSwap(A, 0, sizeof(A) / sizeof(A[0])-1);
	for (int i = 0; i < sizeof(A) / sizeof(A[0]); i++)
	{
		cout << A[i] << " ";
	}
}

int main()
{
	Test01();
	system("pause");
	return 0;
}