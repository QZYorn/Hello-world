#include<iostream>
using namespace std;
#include<string>

class Base1
{
public:
	Base1()
	{
		m_a = 10000;
		m_b = 20000;
	}

	void func()
	{
		cout << "Base1��func����" << endl;
	}

	void func(int a)
	{
		cout << "Base1��func(int)����" << endl;
	}
	int m_a;
	int m_b;
};

class Base2
{
public:
	Base2()
	{
		m_b = 1000;
	}

	void func()
	{
		cout << "Base2��func����" << endl;
	}

	void func(int a)
	{
		cout << "Base2��func(int)����" << endl;
	}
	int m_b;
};

class Son:public Base1,public Base2
{
public:
	Son()
	{
		m_s = 100;
	}

	void func()
	{
		cout << "Son��func����" << endl;
	}
	int m_s;
};


void Test01()
{
	Son s1;
	//cout << "Base1��m_b = " << s1.m_b << endl;//����ȷ��������
	cout << "Base1��m_b = " << s1.Base1::m_b << endl;//����֮�������ĳ�Ա���������
	cout << "Base1��m_b = " << s1.Base2::m_b << endl;
	s1.func();//���ȵ�������ͬ����Ա����
	//s1.func(10);//����
	s1.Base1::func(10);
}

int main()
{
	Test01();
	return 0;
}