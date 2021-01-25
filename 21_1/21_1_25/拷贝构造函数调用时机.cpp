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
	Person(Person &p)//拷贝
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

void Test01(const Person p)
{
	;
}

Person Test02()
{
	Person p;
	return p;
}

int main()
{
	Person p1(10);
	//Person p2(p1);//创建时拷贝
	//Test01(p2);//传值拷贝
	p1 = Test02();//值方式返回局部对象
	return 0;
}