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

class MyCompare
{
public:
	bool operator()(int a,int b)
	{
		return a > b;
	}
};

void Test01()
{
	set<int> s1;
	s1.insert(20);
	s1.insert(40);
	s1.insert(10);
	s1.insert(60);
	s1.insert(50);
	printSet(s1);
	//默认从小到大

	set<int, MyCompare> s2;//改成从大到小
	s2.insert(20);
	s2.insert(50);
	s2.insert(40);
	s2.insert(60);
	s2.insert(10);
	for (set<int, MyCompare>::iterator it = s2.begin(); it != s2.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

}

int main()
{
	Test01();
	system("pause");
	return 0;
}