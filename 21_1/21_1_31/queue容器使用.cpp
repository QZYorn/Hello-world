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
		cout << "����Ϊ��\t" << m_Name << "  ����Ϊ" << m_Age << endl;
	}
	string m_Name;
	int m_Age;
};

void Test01()
{
	queue<Person> q;
	Person p1("�����", 999);
	Person p2("��˽�", 452);
	Person p3("������", 153);
	Person p4("ɳɮ", 66);
	Person p5("��ɮ", 25);

	q.push(p1);
	q.push(p2);
	q.push(p3);
	q.push(p4);
	q.push(p5);

	while (! q.empty())
	{
		cout << "��ͷ��";
		q.front().showInfo();
		cout << "��β��";
		q.back().showInfo();
		cout << "���д�СΪ��" << q.size() << endl;
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