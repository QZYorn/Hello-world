#include<iostream>
using namespace std;
#include<string>

class Person1
{
public:
	void per01()
	{
		cout << "per01" << endl;
	}
};

class Person2
{
public:
	void per02()
	{
		cout << "per02" << endl;
	}
};

template <class T>
class Fun//��ģ�岢����һ��ʼ�ʹ����������ڵ���ʱ�Ŵ���
{
public:
	T m_per;

	void func01()//δ����ʱ����������δȷ����������
	{
		m_per.per01();
	}

	void func02()
	{
		m_per.per02();
	}
};

void Test01()
{
	Fun<Person1> fp1;
	fp1.func01();
	fp1.m_per.per01();//�ȼ�����
	//fp1.func02();//���������Person1.per02()

	Fun<Person2> fp2;
	//fp2.func01();//���������Person2.per01()
	fp2.func02();
	fp2.m_per.per02();//�ȼ�����
}

int main()
{
	Test01();
	system("pause");
	return 0;
}