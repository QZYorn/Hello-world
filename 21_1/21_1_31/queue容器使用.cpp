#include<iostream>
using namespace std;
#include<queue>
#include<string>

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
		cout << "姓名为：\t" << m_Name << "  年龄为" << m_Age << endl;
	}
	string m_Name;
	int m_Age;
};

void Test01()
{
	queue<Person> q;
	Person p1("孙悟空", 999);
	Person p2("猪八戒", 452);
	Person p3("白龙马", 153);
	Person p4("沙僧", 66);
	Person p5("唐僧", 25);

	q.push(p1);
	q.push(p2);
	q.push(p3);
	q.push(p4);
	q.push(p5);

	while (! q.empty())
	{
		cout << "队头：";
		q.front().showInfo();
		cout << "队尾：";
		q.back().showInfo();
		cout << "队列大小为：" << q.size() << endl;
		q.pop();
		cout << endl;
	}
}



int main()
{
	Test01();
	system("pause");
	return 0;
}