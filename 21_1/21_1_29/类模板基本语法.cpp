#include<iostream>
using namespace std;
#include<string>

template<class TypeName,class TypeAge>//������ģ��
class Person
{
public:
	Person(TypeName name, TypeAge age)
	{
		m_Name = name;
		m_Age = age;
	}

	void showInfo()
	{
		cout << "������" << m_Name << endl;
		cout << "���䣺" << m_Age << endl;
	}

	TypeName m_Name;
	TypeAge m_Age;
};

void Test01()
{
	Person<string, int> p1("�����", 999);
	p1.showInfo();
}

int main()
{
	Test01();
	system("pause");
	return 0;
}