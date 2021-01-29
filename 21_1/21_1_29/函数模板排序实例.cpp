#include<iostream>
using namespace std;

template<typename T>
void Swap(T&a, T&b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template<typename T>
void Sort(T arr[], int len)
{
	int flag;
	for (int i = 0; i < len; i++)
	{
		flag = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[flag] < arr[j])
			{
				flag = j;
			}
		}
		if (flag != i)
		{
			Swap(arr[flag], arr[i]);
		}
	}
}

template<typename T>
void Print(T arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void Test01()
{
	char cArr[] = "aehysfgv";
	int num = sizeof(cArr)/sizeof(char);
	Sort(cArr, num);
	Print(cArr, num);
}

void Test02()
{
	int iArr[] = {2,8,9,5,7,2,6,1};
	int num = sizeof(iArr) / sizeof(int);
	Sort(iArr, num);
	Print(iArr, num);
}

int main()
{
	Test01();
	Test02();
	system("pause");
	return 0;
}