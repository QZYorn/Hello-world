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
	//β��
	li.push_back(10);
	li.push_back(20);
	li.push_back(30);
	//ͷ��
	li.push_front(100);
	li.push_front(1000);
	//1000 100 10 20 30

	cout <<"��ͷ:" <<li.front() << endl;
	cout << "��β:" << li.back() << endl;

	list<int>::iterator it = li.begin();
	it++;
	it--;
	//it = it + 1;//��֧���������
}



int main()
{
	Test01();
	system("pause");
	return 0;
}