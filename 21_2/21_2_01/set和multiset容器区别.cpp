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
	set<int> s1;//默认构造
	pair<set<int>::iterator, bool> it = s1.insert(10);
	if (it.second)
	{
		cout << "第一次插入成功" << endl;
	}
	else
	{
		cout << "第一次插入失败" << endl;
	}
	printSet(s1);

	it = s1.insert(10);
	if (it.second)
	{
		cout << "第二次插入成功" << endl;
	}
	else
	{
		cout << "第二次插入失败" << endl;
	}
	printSet(s1);

	multiset<int> ms;//multiset可插入重复元素
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