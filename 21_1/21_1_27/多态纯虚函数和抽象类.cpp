#include<iostream>
using namespace std;

class Base
{
public:
	//只要有一个纯虚函数，该类就为抽象类
	virtual void func() = 0;//纯虚函数
	int m_a;
};

class Son1 :public Base
{
public:
	int m_s1;
};

class Son2 :public Base
{
public:
	void func()
	{
		cout << "jiejiejie" << endl;
	}
	int m_s2;
};

void Test01()
{
	//Base b;//抽象类不可实例化
	//new Base;
	//Son1 s1;//子类若不重写父类纯虚函数，则自身也为抽象类，不可实例化
	Base *b = NULL;
	//b = new Base;
	b = new Son2;
	b->func();
	b->m_a = 100;
	delete b;
}



int main()
{
	Test01();
	return 0;
}