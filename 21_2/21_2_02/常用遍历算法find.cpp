#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<string>


void Test01()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(40);
	v1.push_back(20);
	v1.push_back(50);
	v1.push_back(70);

	vector<int>::iterator it = find(v1.begin(), v1.end(), 20);
	if (it == v1.end())
	{
		cout << "û�ҵ�" << endl;
	}
	else
	{
		cout << "�ҵ��ˣ���" << *it << endl;
	}
}


class Person
{
public:
	Person(string name, int age)
	{
		m_Name = name;
		m_Age = age;
	}
	//find�㷨���ù����У�����ʵ��ת��Ϊ�������βΣ��޷����÷ǳ��������б�����������
	bool operator==(const Person &p)//==���������
	{
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string m_Name;
	int m_Age;
};

void Test02()
{
	vector<Person> v1;

	Person p1("aaa", 10);
	Person p2("sss", 20);
	Person p3("fff", 60);
	Person p4("ccc", 40);

	v1.push_back(p1);
	v1.push_back(p2);
	v1.push_back(p3);
	v1.push_back(p4);


	Person pp("fff", 60);

	

	vector<Person>::iterator it = find(v1.begin(), v1.end(), pp);
	if (it == v1.end())
	{
		cout << "û�ҵ�" << endl;
	}
	else
	{
		cout << "�ҵ��ˣ������ǣ�" << it->m_Name << "  �����ǣ�" << it->m_Age << endl;
	}
}

int main()
{
	Test01();
	Test02();
	system("pause");
	return 0;
}