#include<iostream>
using namespace std;
#include<list>
#include<string>
class Person
{
public:
	Person(string name, int age, int height)
	{
		m_Name = name;
		m_Age = age;
		m_Height = height;
	}
	string m_Name;
	int m_Age;
	int m_Height;
};
void printList(const list<Person> &li)
{
	for (list<Person>::const_iterator it = li.begin(); it != li.end(); it++)
	{
		cout << "������" << it->m_Name << " ���䣺" << it->m_Age << " ��ߣ�" << it->m_Height;
		cout << endl;
	}
}

bool Compare(Person &p1, Person &p2)
{
	if (p1.m_Age == p2.m_Age)
	{
		return p1.m_Height > p2.m_Height;
	}
	return p1.m_Age < p2.m_Age;
}

void Test01()
{
	list<Person> li;
	Person p1("����", 35, 175);
	Person p2("�ܲ�", 45, 180);
	Person p3("��Ȩ", 40, 170);
	Person p4("����", 25, 190);
	Person p5("�ŷ�", 35, 160);
	Person p6("����", 35, 200);

	li.push_back(p1);
	li.push_back(p2);
	li.push_back(p3);
	li.push_back(p4);
	li.push_back(p5);
	//����ǰ
	printList(li);
	cout << "-------------------------" << endl;
	//�����
	li.sort(Compare);
	printList(li);

}



int main()
{
	Test01();
	system("pause");
	return 0;
}