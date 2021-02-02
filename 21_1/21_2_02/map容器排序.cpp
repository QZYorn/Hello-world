#include<iostream>
using namespace std;
#include<map>
#include<string>
void printMap(map<int, int> &m)
{
	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key:" << it->first << "  value:" << (*it).second << endl;
	}
	cout << endl;
}

class Person
{
public:
	Person(string name, int age)
	{
		m_Name = name;
		m_Age = age;
	}

	string m_Name;
	int m_Age;
};

class MyCompare
{
public:
	bool operator()(int a, int b)
	{
		return a > b;
	}
};

class MyComparePerson
{
public:
	bool operator()(const Person &p1, const Person &p2)
	{
		return p1.m_Age > p2.m_Age;
	}
};

void Test01()
{
	map<int, int,MyCompare> m;//按key从大到小排序
	m.insert(pair<int, int>(1, 10)); 
	m.insert(make_pair(2, 20));
	m.insert(map<int, int>::value_type(3, 40));
	m[4] = 80;

	for (map <int,int, MyCompare>::iterator it = m.begin(); it != m.end();it++)
	{
		cout << "key:" << it->first << "  value:" << (*it).second << endl;
	}
	cout << endl;

	map<Person, int, MyComparePerson> mp;//按年龄从大到小排序
	Person p1("孙悟空", 999);
	Person p2("猪八戒", 666);
	Person p3("白龙马", 254);
	Person p4("唐三藏", 34);
	Person p5("沙师弟", 357);

	mp.insert(pair<Person, int>(p1, 1));
	mp.insert(pair<Person, int>(p2, 2));
	mp.insert(pair<Person, int>(p3, 3));
	mp.insert(pair<Person, int>(p4, 4));
	mp.insert(pair<Person, int>(p5, 5));

	for (map<Person, int>::iterator it = mp.begin(); it != mp.end(); it++)
	{
		cout << "姓名：" << it->first.m_Name << "  年龄：" << it->first.m_Age << endl;
	} 
}

int main()
{
	Test01();
	system("pause");
	return 0;
}