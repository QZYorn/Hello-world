#include<iostream>
using namespace std;
#include<string>

template<class TypeName,class TypeAge = int>
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
	//Person p2("孙悟空", 999);//类模板没有自动类型推导
	Person<string> p2("猪八戒", 999);
	p2.showInfo();//类模板参数列表中可以有默认参数

}

int main()
{
	Test01();
	system("pause");
	return 0;
}