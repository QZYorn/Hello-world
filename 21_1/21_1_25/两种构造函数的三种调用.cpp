#include<iostream>
using namespace std;

class Person
{
public:
	Person()//�޲�
	{
		cout << "���캯������" << endl;
	}
	Person(int a)//�в�
	{
		cout << "�вι��캯������" << endl;
		m_a = a;
	}
	Person(const Person &p)//����
	{
		cout << "�������캯������" << endl;
		m_a = p.m_a;
	}

	~Person()
	{
		cout << "������������" << endl;
	}

private:
	int m_a;
};


int main()
{
	Person p1;//���ŷ�
	Person p2(10);
	Person p3(p2);

	Person p4 = Person();//��ʽ��
	Person p5 = Person(10);
	Person p6 = Person(p5);

	Person p7 = 10;//��ʽת����
	Person p8 = p7;
	return 0;
}