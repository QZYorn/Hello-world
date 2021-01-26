#include<iostream>
using namespace std;
#include<string>

class Base1
{
public:
	Base1()
	{
		m_a = 10000;
		m_b = 20000;
	}

	void func()
	{
		cout << "Base1中func调用" << endl;
	}

	void func(int a)
	{
		cout << "Base1中func(int)调用" << endl;
	}
	int m_a;
	int m_b;
};

class Base2
{
public:
	Base2()
	{
		m_b = 1000;
	}

	void func()
	{
		cout << "Base2中func调用" << endl;
	}

	void func(int a)
	{
		cout << "Base2中func(int)调用" << endl;
	}
	int m_b;
};

class Son:public Base1,public Base2
{
public:
	Son()
	{
		m_s = 100;
	}

	void func()
	{
		cout << "Son中func调用" << endl;
	}
	int m_s;
};


void Test01()
{
	Son s1;
	//cout << "Base1中m_b = " << s1.m_b << endl;//不明确，有歧义
	cout << "Base1中m_b = " << s1.Base1::m_b << endl;//父类之间重名的成员需加作用域
	cout << "Base1中m_b = " << s1.Base2::m_b << endl;
	s1.func();//优先调用子类同名成员函数
	//s1.func(10);//屏蔽
	s1.Base1::func(10);
}

int main()
{
	Test01();
	return 0;
}