#include<iostream>
using namespace std;
#include<string>

class Person1
{
public:
	void per01()
	{
		cout << "per01" << endl;
	}
};

class Person2
{
public:
	void per02()
	{
		cout << "per02" << endl;
	}
};

template <class T>
class Fun//类模板并不在一开始就创建，而是在调用时才创建
{
public:
	T m_per;

	void func01()//未调用时，参数类型未确定，不创建
	{
		m_per.per01();
	}

	void func02()
	{
		m_per.per02();
	}
};

void Test01()
{
	Fun<Person1> fp1;
	fp1.func01();
	fp1.m_per.per01();//等价以上
	//fp1.func02();//变相调用了Person1.per02()

	Fun<Person2> fp2;
	//fp2.func01();//变相调用了Person2.per01()
	fp2.func02();
	fp2.m_per.per02();//等价以上
}

int main()
{
	Test01();
	system("pause");
	return 0;
}