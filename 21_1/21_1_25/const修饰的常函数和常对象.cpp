#include<iostream>
using namespace std;

class Person
{
public:

	void Func1() const//const Person *this const��Ա������
	{
		//m_a = 10;
		//this->m_a = 10;//ָ��ָ���ֵ���ɸ���
		//this = NULL;	 //ָ���ָ�򲻿ɸ���
		m_b = 10;
		this->m_b = 100;
		cout << "jiejiejie" << endl;
	}

	void Func2()
	{
		cout << "yeyeyey" << endl;
	}

	int m_a;
	mutable int m_b;//��������� mutable���εı����ڳ�Ա��������Ҳ���޸�
};


void Test01()
{
	Person p1;
	p1.Func1();
	p1.Func2();
	const Person p2;//const���κ��Ϊ������
	/*p2.m_a = 10;
	p2.Func2();*///�����󲻿ɷ��� �ǳ�����
	p2.Func1();//���ɵ��ó�����
	p2.m_b = 333;//���������ͬ�����ɷ���mutable���εı���
}

int main()
{
	Test01();
	return 0;
}