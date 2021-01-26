#include<iostream>
using namespace std;
#include<assert.h>

class Person
{

public:
	Person(int age)
	{
		m_Age = new int(age);//在堆区开辟内存
	}

	Person& operator=(Person &p)//重载 赋值运算符
	{
		if (m_Age != NULL)//释放本对象之前开辟的堆区内存，避免内存泄漏
		{
			delete m_Age;
			m_Age = NULL;
		}
		this->m_Age = new int(*p.m_Age);//开辟新堆区内存存放 新赋的值，深拷贝
		return *this;//返回对象本身，实现链式编程
	}

	~Person()
	{
		assert(m_Age != NULL);
		delete m_Age;//释放堆区内存
		m_Age = NULL;
	}

	int *m_Age;
};

void Test01()
{
	Person p1(15);
	Person p2(10);
	Person p3(30);
	p3 = p1 = p2;
	cout << "p1 = " << *p1.m_Age << endl;
	cout << "p2 = " << *p2.m_Age << endl;
	cout << "p3 = " << *p3.m_Age << endl;
}
int main()
{
	Test01();
	return 0;
}