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
	
	printSet(s1);

	set<int>::iterator pos = s1.find(40);
	if (pos != s1.end())
	{
		cout << "�ҵ��ˣ�" << *pos << endl;
		cout << "Ԫ�ظ���Ϊ��" << s1.count(40) << endl;
	}
	else
	{
		cout << "û�ҵ�" << endl;
	}
}

int main()
{
	Test01();
	system("pause");
	return 0;
}