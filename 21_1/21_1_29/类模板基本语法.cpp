#include<iostream>
using namespace std;
#include<string>

template<class TypeName,class TypeAge>//声明类模板
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
		cout << "姓名：" << m_Name << endl;
		cout << "年龄：" << m_Age << endl;
	}

	TypeName m_Name;
	TypeAge m_Age;
};

void Test01()
{
	Person<string, int> p1("孙悟空", 999);
	p1.showInfo();
}

int main()
{
	Test01();
	system("pause");
	return 0;
}