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
	deque<int> d1;
	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
	}

	if (d1.empty())
	{
		cout << "为空" << endl;
	}
	else
	{
		cout << "大小为：" << d1.size() << endl;
		printDeque(d1);
	}

	d1.resize(20);//默认补全0
	printDeque(d1);
	d1.resize(25, 100);//用100补全
	printDeque(d1);
	d1.resize(3);//只保留三个元素，后续删除
	printDeque(d1);
}



int main()
{
	Test01();
	system("pause");
	return 0;
}