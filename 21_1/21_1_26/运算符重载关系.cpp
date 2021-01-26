#include<iostream>
using namespace std;
#include<string>

class Person
{
public:
	Person(string name, int age)
	{
		m_Name = name;
		m_Age = age;
	}

	bool operator==(Person &p)//��ϵ�����== ����
	{
		if (m_Name == p.m_Name && m_Age == p.m_Age)
		{
			return true;
		}
		return false;
	}

	bool operator!=(Person &p)//��ϵ�������= ����
	{
		if (m_Name == p.m_Name && m_Age == p.m_Age)
		{
			return false;
		}
		return true;
	}


private:
	string m_Name;
	int m_Age;
};

void Test01()
{
	Person p1("����", 10);
	Person p2("����", 10);
	Person p3("����", 6);
	if (p1 == p2)
	{
		cout << "p1��p2���" << endl;
	}
	else
	{
		cout << "p1��p2����ȣ�����" << endl;
	}

	if (p1 != p3)
	{
		cout << "p1��p3���" << endl;
	}
	else
	{
		cout << "p1��p3����ȣ�����" << endl;
	}
}
int main()
{
	Test01();
	return 0;
}