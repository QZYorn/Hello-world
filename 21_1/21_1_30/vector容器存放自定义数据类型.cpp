#include<iostream>
#include<string>
using namespace std;
#include<vector>

class Person
{
public:
	Person(string name, int age)
	{
		m_Name = name;
		m_Age = age;
	}

	void showInfo()
	{
		cout << "姓名：" << m_Name << "  年龄：" << m_Age << endl;
	}
	string m_Name;
	int m_Age;
};

void Test01()
{
	vector<Person> p;
	Person p1("哩哩", 15);
	Person p2("大大", 34);
	Person p3("高度", 53);
	Person p4("十的", 23);
	Person p5("阅读", 62);

	p.push_back(p1);
	p.push_back(p2);
	p.push_back(p3);
	p.push_back(p4);
	p.push_back(p5);

	for (vector<Person>::iterator it = p.begin(); it != p.end(); it++)
	{
		it->showInfo();
	}
}

int main()
{
	Test01();
	system("pause");
	return 0;
}