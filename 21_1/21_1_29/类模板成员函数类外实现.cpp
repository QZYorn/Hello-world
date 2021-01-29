#include<iostream>
using namespace std;
#include<string>

template<class T1,class T2>
class Person
{
public:
	Person(T1 name, T2 age);//��������
	void showInfo();

	T1 m_Name;
	T2 m_Age;
};

template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age)//����ʵ��
{
	m_Name = name;
	m_Age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showInfo()
{
	cout << "������" << m_Name << endl;
	cout << "���䣺" << m_Age << endl;
}


void Test01()
{
	Person<string, int> p1("�����", 999);
	p1.showInfo();
}

int main()
{
	Test01();
	system("pause");
	return 0;
}