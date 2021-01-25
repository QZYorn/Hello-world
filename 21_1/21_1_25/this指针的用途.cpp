#include<iostream>
using namespace std;

class Person
{
public:
	Person(int age) :m_a(9)
	{
		this->age = age;//1.形参和成员变量重名
	}

	Person& func(Person &p)
	{
		this->age += p.age;
		return *this;//2.返回对象自己本身
	}

	int m_a;
	int age;
};

void Test01()
{
	Person p1(10);
	Person p2(5);
	p1.func(p2).func(p2).func(p2);//10+5+5+5
	p2.func(p2).func(p2).func(p2);//10*2*2*2
	
	cout << p1.age << endl;
	cout << p2.age << endl;

}

int main()
{
	Test01();
	return 0;
}