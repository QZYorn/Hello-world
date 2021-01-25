#include<iostream>
using namespace std;

class Person
{
public:

	void static func()
	{
		cout << "void static func() " << endl;
		m_a = 999;//可访问静态成员函数
		m_b = 666;
		//m_c = 111;//不可访问非静态成员函数
	}

	static int m_a;//公开静态变量

private:
	void static func2()
	{
		cout << "void static func() " << endl;
		m_a = 999;//可访问静态成员函数
		m_b = 666;
		//m_c = 111;//不可访问非静态成员函数
	}

	static int m_b;//私有静态变量
	int m_c;
};

int Person::m_a = 100;//初始化
int Person::m_b = 200;
void Test()
{
	Person p1;
	p1.func();//通过对象访问
	Person::func();//通过类名访问
	//p1.func2();//访问权限受限
	//Person::func2();//
	//cout << "p1.m_a = " << Person::m_b << endl;//访问权限限制

}
int main()
{
	Test();
	return 0;
}