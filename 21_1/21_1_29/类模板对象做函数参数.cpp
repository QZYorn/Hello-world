#include<iostream>
using namespace std;
#include<string>

template<class T1, class T2>
class Person
{
public:
	Person(T1 name, T2 age) 
	{
		m_Name = name;
		m_Age = age;
	}

	void showInfo()
	{
		cout << "名字：" << m_Name << endl;
		cout << "年龄：" << m_Age << endl;
	}

	T1 m_Name;
	T2 m_Age;
};

void func1(Person<string, int> &p)//普通传参，具体类型
{
	p.showInfo();
}

template<class T1, class T2>
void func2(Person<T1, T2> &p)//类参数列表模板化
{
	p.showInfo();
}

template<class T>
void func3(T &p)//整个类模板化
{
	p.showInfo();
}

void Test01()
{
	Person<string, int> p1("孙悟空", 999);
	func1(p1);
	func2(p1);
	func3(p1);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}