#include<iostream>
using namespace std;

int Sum(int A[], int size)
{
	if (size == 0)
	{
		return 0;
	}
	return Sum(A, size - 1) + A[size - 1];
}

void Test01()
{
	int A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	cout << Sum(A, sizeof(A)/sizeof(A[0]));
}

int main()
{
	Test01();
	system("pause");
	return 0;
}