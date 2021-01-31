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
	//尾插
	li.push_back(10);
	li.push_back(20);
	li.push_back(30);
	//头插
	li.push_front(100);
	li.push_front(1000);
	//1000 100 10 20 30

	//尾删
	li.pop_back();
	//头删
	li.pop_front();
	//100 10 20 
	printList(li);

	list<int>::iterator it = li.begin();
	it++;
	li.insert(it, 3, 9);
	printList(li);
	//100 9 9 9 10 20

	it = li.begin();
	it++;
	li.insert(it, 0);
	printList(li);
	//100 0 9 9 9 10 20

	it = li.begin();
	it++;
	li.erase(it);
	printList(li);
	//100 9 9 9 10 20

	li.remove(9);
	printList(li);
	//100 10 20

	li.clear();


}



int main()
{
	Test01();
	system("pause");
	return 0;
}