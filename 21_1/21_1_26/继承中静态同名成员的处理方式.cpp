#include<iostream>
using namespace std;
#include<string>

class Base
{
public:
	

	static void func()
	{
		cout << "Base��func����" << endl;
	}

	static void func(int a)
	{
		cout << "Base��func(int)����" << endl;
	}
	static int m_a;//��������
};
int Base::m_a = 100;//����ʵ��

class Son:public Base
{
public:

	static void func()
	{
		cout << "Son��func����" << endl;
	}
	static int m_a;
};
int Son::m_a = 200;


void Test01()
{
	Son s1;
	//1.ͨ���������
	cout << "ͨ���������:" << endl;
	cout << "Son  �� m_a = " << s1.m_a << endl;//����ͬ����Ա��ֱ�ӷ���
	cout << "Base �� m_a = " << s1.Base::m_a << endl;//����ͬ����Ա�������������
	s1.func();//����ͬ����Ա��ֱ�ӷ���
	//s1.func(10);//����ͬ����Ա������
	s1.Base::func();//����ͬ����Ա�������������
	s1.Base::func(10);

	cout << endl ;

	//2.ͨ����������
	cout << "ͨ���������ʣ�" << endl;
	cout << "Son  �� m_a = " << Son::m_a << endl;//����ͬ����Ա��ֱ�ӷ���
	cout << "Base �� m_a = " << Son::Base::m_a << endl;//����ͬ����Ա�������������
	Son::func();
	//Son::func(10);
	Son::Base::func();
	Son::Base::func(10);//��һ��::Ϊ�������ʣ��ڶ���::ΪBase��������
}

int main()
{
	Test01();
	return 0;
}