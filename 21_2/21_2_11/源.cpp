#include<iostream>
using namespace std;
#include"MyVector.hpp"

void Test01()
{
	int arr[] = { 1, 2, 3, 5, 8, 4, 8 };
	//MyVector<int> mv;//默认 构造
	MyVector<int> mv(arr, 0, sizeof(arr)/sizeof(arr[0]));//拷贝 数组区间 构造
	MyVector<int> mv1(mv, 0, 3);//拷贝 向量区间 构造
	MyVector<int> mv2(mv);//拷贝 向量整体 构造
	for (int i = 0; i < mv.size(); i++)
	{
		cout << mv[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < mv1.size(); i++)
	{
		cout << mv1[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < mv2.size(); i++)
	{
		cout << mv2[i] << " ";
	}
}


int main()
{
	Test01();
	system("pause");
	return 0;
}