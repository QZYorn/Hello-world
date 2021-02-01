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

	s1.erase(s1.begin());
	//ɾ����ʼλ�õ�Ԫ��
	printSet(s1);

	s1.erase(70);
	//ɾ��Ϊ70��Ԫ��
	printSet(s1);

	s1.erase(s1.begin(), s1.end());
	//ɾ��������Ԫ��
	printSet(s1);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}