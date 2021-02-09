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
	bool operator()(const Person &p1, const Person &p2)
	{
		return p1.m_Age>p2.m_Age;//���䰴����
	}
};

void Test01()
{
	set<Person,MyCompare> s1;
	Person p1("�����", 999);
	Person p2("��˽�", 658);
	Person p3("ɳɮ", 258);
	Person p4("��ɮ", 26);
	Person p5("������", 156);

	s1.insert(p1);
	s1.insert(p2);
	s1.insert(p3);
	s1.insert(p4);
	s1.insert(p5);

	for (set<Person, MyCompare>::iterator it = s1.begin(); it != s1.end(); it++)
	{
		cout << "������" << it->m_Name << "  ���䣺" << it->m_Age << endl;
	}
}

int main()
{
	Test01();
	system("pause");
	return 0;
}