#include<iostream>
using namespace std;

class Person
{
public:
	/*Person(int a,int b, int c)
	{
		m_a = a;
		m_b = b;
		m_c = c;
		cout << "���캯������" << endl;
	}*/

	//Person() :m_a(10), m_b(20), m_c(30)//��ʼ���б�
	//{
	//	cout << "���캯������" << endl;
	//}

	Person(int a, int b, int c) :m_a(a), m_b(b), m_c(c)//��ʼ���б�
	{
		cout << "���캯������" << endl;
	}

	~Person()
	{
		cout << "������������" << endl;
	}


	int m_a;
	int m_b;
	int m_c;
};

void Test()
{
	//Person p1(10, 20, 30);
	Person p1(10, 20, 30);
	cout << "m_a = " << p1.m_a << endl;
	cout << "m_b = " << p1.m_b << endl;
	cout << "m_c = " << p1.m_c << endl;
}

int main()
{
	Test();
	return 0;
}