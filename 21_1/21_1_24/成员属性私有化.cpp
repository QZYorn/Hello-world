#include<iostream>
#include<string>
using namespace std;

class Person
{
public:
	string getName()//������
	{
		return m_name;
	}
	void setName(string name)//д����
	{
		m_name = name;
	}

	int getAge()//������
	{
		return m_age;
	}
	void setAge(int age)//д����
	{
		if (age<0 || age>150)
		{
			cout << "ƭ������" << endl;
			m_age = 0;
			return;
		}
		m_age = age;
	}


	void setLover(string lover)//д����
	{
		m_lover = lover;
	}


private:
	string m_name = "����";//���� �ɶ���д
	int m_age = 18;//���� �ɶ� ��д
	string m_lover = "����";//���� ��д

};

int main()
{
	Person p1;
	cout << "������" << p1.getName() << endl;
	p1.setName("����");
	cout << "�޸ĺ�������" << p1.getName() << endl;
	cout << "������" << p1.getAge() << endl;
	p1.setAge(100);
	p1.setAge(666);
	cout << "�޸ĺ�������" << p1.getAge() << endl;

	//p1.setAge;
	//p1.m_age = 10;
	p1.setLover("����");
	return 0;
}