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

bool Compare(int v1, int v2)
{
	return v1 > v2;
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
	printList(li);

	//��ת
	li.reverse();
	printList(li);

	//��С��������
	li.sort();
	printList(li);

	//�Ӵ�С
	li.sort(Compare);
	printList(li);
}



int main()
{
	Test01();
	system("pause");
	return 0;
}