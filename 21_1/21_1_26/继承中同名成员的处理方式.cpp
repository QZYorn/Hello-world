#include<iostream>
using namespace std;
#include<string>

class Base
{
public:
	Base()
	{
		m_a = 100;
	}

	void func()
	{
		cout << "Base��func����" << endl;
	}

	void func(int a)
	{
		cout << "Base��func(int)����" << endl;
	}
	int m_a;
};

class Son:public Base
{
public:
	Son()
	{
		m_a = 200;
	}

	void func()
	{
		cout << "Son��func����" << endl;
	}
	int m_a;
};

void Test01()
{
	Son s1;
	s1.func();//����̳и���ͬ����Ա�����ȷ�������ͬ����Ա
	cout << "m_a = " << s1.m_a << endl;
	s1.Base::func();//��Ҫ���ʸ���ͬ����Ա�����������
	cout << "m_a = " << s1.Base::m_a << endl;
	//s1.func(10);//�����븸���Աͬ������������ظ�������ͬ����Ա
	s1.Base::func(10);
}

int main()
{
	Test01();
	return 0;
}