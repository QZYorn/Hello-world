#include<iostream>
using namespace std;

class Person
{
public:
	Person()//�޲�
	{
		cout << "���캯������" << endl;
	}
	Person(int a, int b)//�в�
	{
		cout << "�вι��캯������" << endl;
		m_a = a;
		m_Heigh = new int(b);
	}
	Person(const Person &p)//����
	{
		cout << "�������캯������" << endl;
		m_a = p.m_a;
		if (p.m_Heigh != NULL)
		{
			m_Heigh = new int(*p.m_Heigh);
		}
	}

	~Person()
	{
		if (m_Heigh != NULL)
		{
			delete m_Heigh;
			m_Heigh = NULL;
		}
		cout << "������������" << endl;
	}

	int m_a;
	int *m_Heigh;
};



int main()
{
	Person p1(10,160);
	Person p2(p1);
	cout << p1.m_Heigh << endl;
	cout << p2.m_Heigh << endl;
	return 0;
}