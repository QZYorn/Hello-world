#include<iostream>
using namespace std;
#include<deque>

void printDeque(const deque<int> &d)
{
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		//*it = 100;
		cout << *it << " ";
	}
	cout << endl;
}

void Test01()
{
	//默认构造
	deque<int> d1;

	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
	}
	printDeque(d1);

	//用[d1.begin(), d1.end())的值构造
	deque<int> d2(d1.begin(), d1.end());
	printDeque(d2);

	//用10个100构造
	deque<int> d3(10, 100);
	printDeque(d3);

	//拷贝构造
	deque<int> d4(d3);
	printDeque(d4);
}



int main()
{
	Test01();
	system("pause");
	return 0;
}