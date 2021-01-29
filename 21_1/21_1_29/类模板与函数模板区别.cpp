#include<iostream>
using namespace std;
#include<string>

template<class TypeName,class TypeAge = int>
class Person
{
public:
	Person(TypeName name, TypeAge age)
	{
		m_Name = name;
		m_Age = age;
	}

	void showInfo()
	{
		cout << "������" << m_Name << endl;
		cout << "���䣺" << m_Age << endl;
	}

	TypeName m_Name;
	TypeAge m_Age;
};

void Test01()
{
	Person<string, int> p1("�����", 999);
	p1.showInfo();
	//Person p2("�����", 999);//��ģ��û���Զ������Ƶ�
	Person<string> p2("��˽�", 999);
	p2.showInfo();//��ģ������б��п�����Ĭ�ϲ���

}

int main()
{
	Test01();
	system("pause");
	return 0;
}