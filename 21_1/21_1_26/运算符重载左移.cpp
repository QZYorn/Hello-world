#include<iostream>
using namespace std;

class Person
{
	friend ostream& operator<<(ostream &out, Person &p);//友元全局函数
public:
	Person(int a, int b)
	{
		m_a = a;
		m_b = b;
	}
	
private:
	int m_a;
	int m_b;
};

//全局函数实现左移运算符重载
//输出自定义数据类型
ostream& operator<<(ostream &out, Person &p)//operate<<(cout, p) 等价  cout << p
{
	out << "m_a = " << p.m_a << "    m_b = " << p.m_b;//链式编程思想
	return out;
}

void Test01()
{
	Person p1(10,10);
	/*p1.m_a = 10;
	p1.m_b = 10;*/
	cout << p1 <<"   jiejiejie" << endl;
	cout << "jiejiejie   " << p1 << endl;

}

int main()
{
	Test01();
	return 0;
}