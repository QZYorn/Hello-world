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
	string m_Name;
	int m_Age;
};

template<typename T>
bool Compare(T &a, T &b)
{
	if (a == b)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<> bool Compare(Person &p1, Person &p2)//���廯Person����ģ�壬���⴦�������ڳ���ģ��
{
	if (p1.m_Name == p2.m_Name && p1.m_Age == p2.m_Age)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Test01()
{
	int a = 10;
	int b = 10;
	int c = 20;
	char d = 'd';
	char e = 'd';
	Person p1("����", 10);
	Person p2("����", 10);
	Person p3("����", 11);

	bool ret;
	//ret= Compare(a, b);
	//ret = Compare(a, c);
	//ret = Compare(e, d);
	//ret = Compare(p1, p2);//�Զ������Ͳ���ֱ�ӱȽ�
	//ret = Compare(p1, p2);
	ret = Compare(p1, p3);

	if (ret)
	{
		cout << "�������" << endl;
	}
	else
	{
		cout << "���ǲ����" << endl;
	}
}



int main()
{
	Test01();
	system("pause");
	return 0;
}