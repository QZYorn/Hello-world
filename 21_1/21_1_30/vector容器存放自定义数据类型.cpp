#include<iostream>
#include<string>
using namespace std;
#include<vector>

class Person
{
public:
	Person(string name, int age)
	{
		m_Name = name;
		m_Age = age;
	}

	void showInfo()
	{
		cout << "������" << m_Name << "  ���䣺" << m_Age << endl;
	}
	string m_Name;
	int m_Age;
};

void Test01()
{
	vector<Person> p;
	Person p1("����", 15);
	Person p2("���", 34);
	Person p3("�߶�", 53);
	Person p4("ʮ��", 23);
	Person p5("�Ķ�", 62);

	p.push_back(p1);
	p.push_back(p2);
	p.push_back(p3);
	p.push_back(p4);
	p.push_back(p5);

	for (vector<Person>::iterator it = p.begin(); it != p.end(); it++)
	{
		it->showInfo();
	}
}

int main()
{
	Test01();
	system("pause");
	return 0;
}