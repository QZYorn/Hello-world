#include<iostream>
using namespace std;
#include<list>

void printList(const list<int> &li)
{
	for (list<int>::const_iterator it = li.begin(); it != li.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void Test01()
{
	list<int> li;//默认构造
	li.push_back(10);
	li.push_back(20);
	li.push_back(30);
	li.push_front(100);
	li.push_front(1000);

	printList(li);

	list<int> li2(li);//拷贝构造
	printList(li2);

	list<int> li3(li2.begin(), li2.end());//区间构造
	printList(li3);

	list<int> li4(10, 100);//构造函数将10个100拷贝构造给li4
	printList(li4);
}



int main()
{
	Test01();
	system("pause");
	return 0;
}