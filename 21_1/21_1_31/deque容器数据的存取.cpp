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
	deque<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_front(100);
	v1.push_front(200);
	//200 100 10 20
	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1.at(i) << " ";
	}
	cout << endl;

	cout << "第一个元素为：" << v1.front() << endl;
	cout << "最后一个元素为：" << v1.back() << endl;
}



int main()
{
	Test01();
	system("pause");
	return 0;
}