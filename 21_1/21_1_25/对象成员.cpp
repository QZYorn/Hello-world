#include<iostream>
using namespace std;
#include<string>

class Phone
{
public:
	Phone(string pname) :p_Pname(pname)
	{
		cout << "phone�Ĺ��캯��" << endl;
	}

	~Phone()
	{
		cout << "person����������" << endl;
	}

	string p_Pname;
};

class Person
{
public:
	Person(string name, string pname) :m_Name(name), m_Phone(pname)
	{
		cout << "person�Ĺ��캯��"<< endl;
	}

	~Person()
	{
		cout << "person����������" << endl;
	}

	string m_Name;
	Phone m_Phone;//�����Ա
};

void Test()
{
	Person p1("����", "oppoR15");
	cout << p1.m_Name << "����:" << p1.m_Phone.p_Pname << endl;
}
int main()
{
	Test();
	return 0;
}