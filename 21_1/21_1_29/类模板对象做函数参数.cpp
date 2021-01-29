#include<iostream>
using namespace std;
#include<string>

template<class T1, class T2>
class Person
{
public:
	Person(T1 name, T2 age) 
	{
		m_Name = name;
		m_Age = age;
	}

	void showInfo()
	{
		cout << "���֣�" << m_Name << endl;
		cout << "���䣺" << m_Age << endl;
	}

	T1 m_Name;
	T2 m_Age;
};

void func1(Person<string, int> &p)//��ͨ���Σ���������
{
	p.showInfo();
}

template<class T1, class T2>
void func2(Person<T1, T2> &p)//������б�ģ�廯
{
	p.showInfo();
}

template<class T>
void func3(T &p)//������ģ�廯
{
	p.showInfo();
}

void Test01()
{
	Person<string, int> p1("�����", 999);
	func1(p1);
	func2(p1);
	func3(p1);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}