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
	list<int> li;//Ĭ�Ϲ���
	li.push_back(10);
	li.push_back(20);
	li.push_back(30);
	li.push_front(100);
	li.push_front(1000);

	if (li.empty())
	{
		cout << "����Ϊ��" << endl;
	}
	else
	{
		cout << "������Ϊ��" << li.size() << endl;
	}
	li.resize(15);
	printList(li);
	li.resize(20,1000);
	printList(li);
	li.resize(5);
	printList(li);

}



int main()
{
	Test01();
	system("pause");
	return 0;
}