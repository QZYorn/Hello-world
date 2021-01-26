#include<iostream>
using namespace std;
#include<assert.h>

class Person
{

public:
	Person(int age)
	{
		m_Age = new int(age);//�ڶ��������ڴ�
	}

	Person& operator=(Person &p)//���� ��ֵ�����
	{
		if (m_Age != NULL)//�ͷű�����֮ǰ���ٵĶ����ڴ棬�����ڴ�й©
		{
			delete m_Age;
			m_Age = NULL;
		}
		this->m_Age = new int(*p.m_Age);//�����¶����ڴ��� �¸���ֵ�����
		return *this;//���ض�����ʵ����ʽ���
	}

	~Person()
	{
		assert(m_Age != NULL);
		delete m_Age;//�ͷŶ����ڴ�
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