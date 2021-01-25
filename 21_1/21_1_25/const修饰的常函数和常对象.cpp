#include<iostream>
using namespace std;

class Person
{
public:

	void Func1() const//const Person *this const成员常函数
	{
		//m_a = 10;
		//this->m_a = 10;//指针指向的值不可更改
		//this = NULL;	 //指针的指向不可更改
		m_b = 10;
		this->m_b = 100;
		cout << "jiejiejie" << endl;
	}

	void Func2()
	{
		cout << "yeyeyey" << endl;
	}

	int m_a;
	mutable int m_b;//特殊情况， mutable修饰的变量在成员常函数内也可修改
};


void Test01()
{
	Person p1;
	p1.Func1();
	p1.Func2();
	const Person p2;//const修饰后成为常对象
	/*p2.m_a = 10;
	p2.Func2();*///常对象不可访问 非常函数
	p2.Func1();//仅可调用常函数
	p2.m_b = 333;//特殊情况：同样，可访问mutable修饰的变量
}

int main()
{
	Test01();
	return 0;
}