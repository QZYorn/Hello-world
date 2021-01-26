#include<iostream>
using namespace std;
#include<string>

class Base
{
public:
	Base()
	{
		m_a = 100;
	}

	void func()
	{
		cout << "Base中func调用" << endl;
	}

	void func(int a)
	{
		cout << "Base中func(int)调用" << endl;
	}
	int m_a;
};

class Son:public Base
{
public:
	Son()
	{
		m_a = 200;
	}

	void func()
	{
		cout << "Son中func调用" << endl;
	}
	int m_a;
};

void Test01()
{
	Son s1;
	s1.func();//子类继承父类同名成员后，优先访问子类同名成员
	cout << "m_a = " << s1.m_a << endl;
	s1.Base::func();//若要访问父类同名成员，需加作用域
	cout << "m_a = " << s1.Base::m_a << endl;
	//s1.func(10);//子类与父类成员同名后，子类会隐藏父类所有同名成员
	s1.Base::func(10);
}

int main()
{
	Test01();
	return 0;
}