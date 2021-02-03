#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

class Person
{
public:
	Person(string name, int age)
	{
		m_Name = name;
		m_Age = age;
	}

	bool operator==( const Person &p)
	{
		if (this->m_Age == p.m_Age)
		{
			return true;
		}
		return false;
	}
	string m_Name;
	int m_Age;
};

void test01()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(10);
	v.push_back(20);
	v.push_back(10);
	v.push_back(40);
	v.push_back(10);

	int num = count(v.begin(), v.end(), 10);
	cout << "有" << num << "个10" << endl;

	vector<Person> vp;
	Person p1("刘备", 35);
	Person p2("张飞", 35);
	Person p3("关羽", 35);
	Person p4("赵云", 25);
	Person p5("张角", 40);

	vp.push_back(p1);
	vp.push_back(p2);
	vp.push_back(p3);
	vp.push_back(p4);
	vp.push_back(p5);

	Person pp("诸葛亮", 35);

	num = count(vp.begin(), vp.end(), pp);
	cout << "有" << num << "个人和诸葛亮年龄相等" << endl;
}

int main()
{
	test01();
	system("pause");
	return 0;
}