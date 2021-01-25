#include<iostream>
using namespace std;

class Person
{
public:
	Person()//无参
	{
		cout << "构造函数调用" << endl;
	}
	Person(int a)//有参
	{
		cout << "有参构造函数调用" << endl;
		m_a = a;
	}
	Person(const Person &p)//拷贝
	{
		cout << "拷贝构造函数调用" << endl;
		m_a = p.m_a;
	}

	~Person()
	{
		cout << "析构函数调用" << endl;
	}

private:
	int m_a;
};


int main()
{
	Person p1;//括号法
	Person p2(10);
	Person p3(p2);

	Person p4 = Person();//显式法
	Person p5 = Person(10);
	Person p6 = Person(p5);

	Person p7 = 10;//隐式转换法
	Person p8 = p7;
	return 0;
}