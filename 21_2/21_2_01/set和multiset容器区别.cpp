#include<iostream>
using namespace std;
#include<set>

void printSet(set<int> &s)
{
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void Test01()
{
	set<int> s1;//Ĭ�Ϲ���
	pair<set<int>::iterator, bool> it = s1.insert(10);
	if (it.second)
	{
		cout << "��һ�β���ɹ�" << endl;
	}
	else
	{
		cout << "��һ�β���ʧ��" << endl;
	}
	printSet(s1);

	it = s1.insert(10);
	if (it.second)
	{
		cout << "�ڶ��β���ɹ�" << endl;
	}
	else
	{
		cout << "�ڶ��β���ʧ��" << endl;
	}
	printSet(s1);

	multiset<int> ms;//multiset�ɲ����ظ�Ԫ��
	ms.insert(10);
	ms.insert(10);
	ms.insert(10);
	ms.insert(10);
	for (multiset<int>::iterator pos = ms.begin(); pos != ms.end(); pos++)
	{
		cout << *pos << " ";
	}
}

int main()
{
	Test01();
	system("pause");
	return 0;
}