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
	s1.insert(10);
	s1.insert(40);
	s1.insert(20);
	s1.insert(70);
	s1.insert(40);
	
	printSet(s1);

	s1.erase(s1.begin());
	//删除起始位置的元素
	printSet(s1);

	s1.erase(70);
	//删除为70的元素
	printSet(s1);

	s1.erase(s1.begin(), s1.end());
	//删除区间内元素
	printSet(s1);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}