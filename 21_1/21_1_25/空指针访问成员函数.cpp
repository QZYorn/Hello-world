#include<iostream>
using namespace std;
#include<assert.h>

class Person
{
public:
	void func1()
	{
		cout << "jiejiejie" << endl;
	}
	void func2()
	{
		assert(this != NULL);
		cout << "yeyeeye" << m_a << endl;
	}
	int m_a;
};

void Test01()
{
	Person *p =NULL;
	p->func1();
	p->func2();
}

int main()
{
	Test01();
	return 0;
}