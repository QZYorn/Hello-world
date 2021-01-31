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

	list<int> li2;
	li2 = li;
	printList(li2);

	cout << "交换前" << endl;
	li2.assign(10, 100);
	printList(li2);

	list<int> li4;
	li4.assign(li.begin(),li.end());
	printList(li4);

	cout << "交换后" << endl;
	li2.swap(li4);
	printList(li2);
	printList(li4);

}



int main()
{
	Test01();
	system("pause");
	return 0;
}