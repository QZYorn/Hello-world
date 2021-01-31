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
	printDeque(d1);

	deque<int> d2;
	d2 = d1;//赋值运算符重载，将d1拷贝赋值给d2
	printDeque(d2);

	deque<int> d3;
	d3.assign(d2.begin(),d2.end());//将区间内值拷贝赋值给d3
	printDeque(d3);

	d3.assign(10, 100);//将10个100拷贝赋值给d3
	printDeque(d3);
}



int main()
{
	Test01();
	system("pause");
	return 0;
}