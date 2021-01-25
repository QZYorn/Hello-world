#include<iostream>
using namespace std;
#include<string>

class Phone
{
public:
	Phone(string pname) :p_Pname(pname)
	{
		cout << "phone的构造函数" << endl;
	}

	~Phone()
	{
		cout << "person的析构函数" << endl;
	}

	string p_Pname;
};

class Person
{
public:
	Person(string name, string pname) :m_Name(name), m_Phone(pname)
	{
		cout << "person的构造函数"<< endl;
	}

	~Person()
	{
		cout << "person的析构函数" << endl;
	}

	string m_Name;
	Phone m_Phone;//对象成员
};

void Test()
{
	Person p1("王五", "oppoR15");
	cout << p1.m_Name << "拿着:" << p1.m_Phone.p_Pname << endl;
}
int main()
{
	Test();
	return 0;
}