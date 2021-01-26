#include<iostream>
using namespace std;
#include<string>

class Base
{
public:
	

	static void func()
	{
		cout << "Base中func调用" << endl;
	}

	static void func(int a)
	{
		cout << "Base中func(int)调用" << endl;
	}
	static int m_a;//类内声明
};
int Base::m_a = 100;//类外实现

class Son:public Base
{
public:

	static void func()
	{
		cout << "Son中func调用" << endl;
	}
	static int m_a;
};
int Son::m_a = 200;


void Test01()
{
	Son s1;
	//1.通过对象访问
	cout << "通过对象访问:" << endl;
	cout << "Son  下 m_a = " << s1.m_a << endl;//子类同名成员可直接访问
	cout << "Base 下 m_a = " << s1.Base::m_a << endl;//父类同名成员访问需加作用域
	s1.func();//子类同名成员可直接访问
	//s1.func(10);//父类同名成员被屏蔽
	s1.Base::func();//父类同名成员访问需加作用域
	s1.Base::func(10);

	cout << endl ;

	//2.通过类名访问
	cout << "通过类名访问：" << endl;
	cout << "Son  下 m_a = " << Son::m_a << endl;//子类同名成员可直接访问
	cout << "Base 下 m_a = " << Son::Base::m_a << endl;//父类同名成员访问需加作用域
	Son::func();
	//Son::func(10);
	Son::Base::func();
	Son::Base::func(10);//第一个::为类名访问，第二个::为Base作用域下
}

int main()
{
	Test01();
	return 0;
}