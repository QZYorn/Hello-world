#include<iostream>
using namespace std;

class Person
{
	friend ostream& operator<<(ostream &out, Person &p);
public:
	Person()
	{
		m_a = 0;
	}

	Person& operator++()//递增前置运算符重载
	{
		m_a++;//先++
		return *this;//再返回
	}
	Person operator++(int)//递增后置运算符重载
	{
		Person tmp = *this;//先记录
		m_a++;//再++
		return tmp;//返回记录值，即++前
	}
	Person& operator--()//递减前置运算符重载
	{
		m_a--;
		return *this;
	}
	Person operator--(int)//递增后置运算符重载
	{
		Person tmp = *this;
		m_a--;
		return tmp;
	}

private:
	int m_a;
};

//<<运算符重载
ostream& operator<<(ostream &out, Person &p)
{
	out << "m_a = " << p.m_a;
	return out;
}

void Test01()
{
	Person p1;
	cout << ++(++p1) << endl;
	cout << p1 << endl;
	cout << p1++ << endl;
	cout << p1 << endl;
	cout << --(--p1) << endl;
	cout << p1 << endl;
	cout << p1-- << endl;
	cout << p1 << endl;

}
int main()
{
	Test01();
	return 0;
}