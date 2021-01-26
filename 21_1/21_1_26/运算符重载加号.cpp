#include<iostream>
using namespace std;

class Person
{
public:
	//Person operator+(Person& p)//��Ա����ʵ�����������
	//{
	//	Person tmp;
	//	tmp.m_a = this->m_a + p.m_a;
	//	tmp.m_b = this->m_b + p.m_b;
	//	return tmp;
	//}

	int m_a;
	int m_b;
};

Person operator+(Person &p1, Person &p2)//ȫ�ֺ���ʵ�����������
{
	Person tmp;
	tmp.m_a = p1.m_a + p2.m_a;
	tmp.m_b = p1.m_b + p2.m_b;
	return tmp;
}
Person operator+(Person &p1, int i)//���������Ҳ����ʵ�ֺ�������
{
	Person tmp;
	tmp.m_a = p1.m_a + i;
	tmp.m_b = p1.m_b + i;
	return tmp;
}

void Test01()
{
	Person p1;
	p1.m_a = 10;
	p1.m_b = 10;
	Person p2;
	p2.m_a = 10;
	p2.m_b = 10;
	Person p3 = p1 + p2;
	//p3 = p1.operator+(p2);//��Ա����ʵ����������ص�ʵ��
	cout << "p3.m_a = " << p3.m_a << endl;
	cout << "p3.m_b = " << p3.m_b << endl;

	Person p4 = p1 + p3;
	p4 = operator+(p1, p3);//ȫ�ֺ���ʵ����������ص�ʵ��
	cout << "p4.m_a = " << p4.m_a << endl;
	cout << "p4.m_b = " << p4.m_b << endl;

	Person p4 = p1 + 10;//��������
	p4 = operator+(p1, 10);//ȫ�ֺ���ʵ����������ص�ʵ��
	cout << "p4.m_a = " << p4.m_a << endl;
	cout << "p4.m_b = " << p4.m_b << endl;
}

int main()
{
	Test01();
	return 0;
}