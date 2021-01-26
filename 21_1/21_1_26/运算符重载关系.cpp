#include<iostream>
using namespace std;
#include<string>

class Person
{
public:
	Person(string name, int age)
	{
		m_Name = name;
		m_Age = age;
	}

	bool operator==(Person &p)//关系运算符== 重载
	{
		if (m_Name == p.m_Name && m_Age == p.m_Age)
		{
			return true;
		}
		return false;
	}

	bool operator!=(Person &p)//关系运算符！= 重载
	{
		if (m_Name == p.m_Name && m_Age == p.m_Age)
		{
			return false;
		}
		return true;
	}


private:
	string m_Name;
	int m_Age;
};

void Test01()
{
	Person p1("李四", 10);
	Person p2("李四", 10);
	Person p3("李四", 6);
	if (p1 == p2)
	{
		cout << "p1和p2相等" << endl;
	}
	else
	{
		cout << "p1和p2不相等！！！" << endl;
	}

	if (p1 != p3)
	{
		cout << "p1和p3相等" << endl;
	}
	else
	{
		cout << "p1和p3不相等！！！" << endl;
	}
}
int main()
{
	Test01();
	return 0;
}