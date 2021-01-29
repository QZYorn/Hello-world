#include<iostream>
using namespace std;
#include<string>


template<class T1,class T2>
class Person;

template<class T1, class T2>
void showInfo02(Person<T1, T2> &p)
{
	cout << "姓名：" << p.m_Name << endl;
	cout << "年龄：" << p.m_Age << endl;
}

template<class T1, class T2>
class Person
{
	friend void showInfo01(Person<T1,T2> &p)//类内实现
	{
		cout << "姓名：" << p.m_Name << endl;
		cout << "年龄：" << p.m_Age << endl;
	}

	//需加空<>参数列表表明为函数模板
	friend void showInfo02<T1,T2>(Person<T1, T2> &p);//类外实现

public:
	Person(T1 name, T2 age)
	{
		m_Name = name;
		m_Age = age;
	}
private:
	T1 m_Name;
	T2 m_Age;
};

void Test01()
{
	Person<string, int> p("孙悟空", 999);
	showInfo01(p);
	showInfo02(p);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}