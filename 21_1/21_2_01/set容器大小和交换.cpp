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
	s1.insert(10);
	s1.insert(40);
	s1.insert(20);
	s1.insert(70);
	s1.insert(40);
	//set������insert����
	//����ʱ�Զ�����
	//�������ظ�����
	cout << "����ǰ��" << endl;
	printSet(s1);

	set<int> s2;
	s2.insert(100);
	s2.insert(400);
	s2.insert(500);
	s2.insert(200);
	s2.insert(100);
	printSet(s2);

	cout << "������" << endl;
	s2.swap(s1);
	printSet(s1);
	printSet(s2);

	if (s1.empty())
	{
		cout << "Ϊ��" << endl;
	}
	else
	{
		cout << "s1����Ϊ" << s1.size() << endl;
	}
}

int main()
{
	Test01();
	system("pause");
	return 0;
}