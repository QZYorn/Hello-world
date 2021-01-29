#include<iostream>
using namespace std;
#include<string>


template<class T1,class T2>
class Person;

template<class T1, class T2>
void showInfo02(Person<T1, T2> &p)
{
	cout << "������" << p.m_Name << endl;
	cout << "���䣺" << p.m_Age << endl;
}

template<class T1, class T2>
class Person
{
	friend void showInfo01(Person<T1,T2> &p)//����ʵ��
	{
		cout << "������" << p.m_Name << endl;
		cout << "���䣺" << p.m_Age << endl;
	}

	//��ӿ�<>�����б����Ϊ����ģ��
	friend void showInfo02<T1,T2>(Person<T1, T2> &p);//����ʵ��

public:
	Person(T1 name, T2 age)
	{
		m_Name = name;
		m_Age = age;
	}
private:
	T1 m_Name;
	T2 m_Age;
};

void Test01()
{
	Person<string, int> p("�����", 999);
	showInfo01(p);
	showInfo02(p);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}