#include<iostream>
#include<string>
using namespace std;
#include<vector>
#include<algorithm>

void func(int a)
{
	cout << a << " ";
}

void Test01()
{
	vector<int> v1;
	for (int i = 10; i <= 50; i += 10)
	{
		v1.push_back(i);
	}
	//vector<typename>::iterator是 vector容器<typename>模板参数的迭代器
	vector<int>::iterator pBegin = v1.begin();//返回指向首元素的迭代器
	vector<int>::iterator pEnd = v1.end();//返回最后一个元素下一个位置的迭代器

	//第一种方法
	for (; pBegin != pEnd; pBegin++)
	{
		cout << *pBegin << " ";
	}
	cout << endl;

	//第二种方法
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;


	//第三种方法
	for_each(v1.begin(), v1.end(), func);//传入（首元素迭代器，结尾迭代器，解引用迭代器传入（func函数指针）即回调函数）
}

int main()
{
	Test01();
	system("pause");
	return 0;
}