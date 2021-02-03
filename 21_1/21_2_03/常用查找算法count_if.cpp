#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

class Person
{
public:
	Person(string name, int age)
	{
		m_Name = name;
		m_Age = age;
	}

	bool operator==( const Person &p)
	{
		if (this->m_Age == p.m_Age)
		{
			return true;
		}
		return false;
	}
	string m_Name;
	int m_Age;
};

class GreaterInt10
{
public:
	bool operator()(int a)//һԪν��
	{
		return a > 10;
	}
};

class GreaterPerson35
{
public:
	bool operator()(const Person &p)
	{
		return p.m_Age > 35;
	}
};

void test01()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(10);
	v.push_back(20);
	v.push_back(10);
	v.push_back(40);
	v.push_back(10);

	int num = count_if(v.begin(), v.end(), GreaterInt10());
	cout << "��" << num << "������10����" << endl;

	vector<Person> vp;
	Person p1("����", 35);
	Person p2("�ŷ�", 35);
	Person p3("����", 35);
	Person p4("����", 25);
	Person p5("�Ž�", 40);

	vp.push_back(p1);
	vp.push_back(p2);
	vp.push_back(p3);
	vp.push_back(p4);
	vp.push_back(p5);


	num = count_if(vp.begin(), vp.end(), GreaterPerson35());
	cout << "��" << num << "�����������35" << endl;
}

int main()
{
	test01();
	system("pause");
	return 0;
}