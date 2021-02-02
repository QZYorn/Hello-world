#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<string>

class CompareInt35
{
public:
	bool operator()(int a)
	{
		return a > 10;
	}
};


void Test01()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(40);
	v1.push_back(20);
	v1.push_back(50);
	v1.push_back(70);

	vector<int>::iterator it = find_if(v1.begin(), v1.end(), CompareInt35());
	if (it == v1.end())
	{
		cout << "找不到" << endl;
	}
	else
	{
		cout << "找到了:" << *it << endl;
	}
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

class ComparePerson35
{
public:
	bool operator()(const Person &p)
	{
		return p.m_Age > 35;
	}
};

void Test02()
{
	vector<Person> v1;

	Person p1("aaa", 10);
	Person p2("sss", 20);
	Person p3("fff", 60);
	Person p4("ccc", 40);

	v1.push_back(p1);
	v1.push_back(p2);
	v1.push_back(p3);
	v1.push_back(p4);

	vector<Person>::iterator it = find_if(v1.begin(), v1.end(), ComparePerson35());
	if (it == v1.end())
	{
		cout << "找不到" << endl;
	}
	else
	{
		cout << "找到了  姓名:" << (*it).m_Name  << "  年龄：" << it->m_Age<< endl;
	}
}

int main()
{
	Test01();
	Test02();
	system("pause");
	return 0;
}