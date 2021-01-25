#include<iostream>
using namespace std;

class Person
{
	int m_a;		//非静态成员变量 占本身大小空间
	static int m_b; //静态成员变量	 不在类对象上
	void func(){}   //非静态成员函数 不在类对象上
	static void func1(){}//静态成员函数 不在类对象上
};
int Person::m_b = 100;


void Test01()
{
	Person p;
	cout << "sizeof为" << sizeof(p) << endl;//空对象大小为1
	cout << "sizeof为" << sizeof(Person) << endl;//空类大小为1
}

void Test02()
{
	Person p;
	cout << "sizeof为" << sizeof(p) << endl;

}

int main()
{
	//Test01();
	Test02();
	return 0;
}