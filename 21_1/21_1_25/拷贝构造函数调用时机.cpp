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
	Person(Person &p)//����
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

void Test01(const Person p)
{
	;
}

Person Test02()
{
	Person p;
	return p;
}

int main()
{
	Person p1(10);
	//Person p2(p1);//����ʱ����
	//Test01(p2);//��ֵ����
	p1 = Test02();//ֵ��ʽ���ؾֲ�����
	return 0;
}