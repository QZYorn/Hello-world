#include<iostream>
using namespace std;
#include<set>
#include<string>

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
	pair<string, int> p("�����", 999);
	cout << "������" << p.first << "  ���䣺" << p.second << endl;

	p = make_pair("��˽�", 582);
	cout << "������" << p.first << "  ���䣺" << p.second << endl;

}

int main()
{
	Test01();
	system("pause");
	return 0;
}