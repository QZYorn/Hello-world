#include<iostream>
using namespace std;

class Person
{
public:
	static int m_a;//公开静态成员变量

private:
	static int m_b;//私有静态成员变量

};

int Person::m_a = 100;//初始化
int Person::m_b = 200;
void Test()
{
	Person p1;
	cout << "p1.m_a = " << p1.m_a << endl;
	cout << "p1.m_a = " << Person::m_a << endl;

	Person p2;
	p2.m_a = 1000;//共享成员
	cout << "p1.m_a = " << p1.m_a << endl;
	cout << "p1.m_a = " << Person::m_a << endl;

	//cout << "p1.m_a = " << Person::m_b << endl;

}
int main()
{
	Test();
	return 0;
}