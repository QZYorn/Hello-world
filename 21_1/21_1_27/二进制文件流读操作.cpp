#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include<assert.h>

class Person
{
public:
	char m_c[10];
	float m_f;
};

void Test01()
{
	ifstream ifs("Person.txt", ios::in | ios::binary);//�������������󣬶�|�����Ʒ�ʽ��
	if (!ifs.is_open())//�жϴ��Ƿ�ɹ�
	{
		cout << "��ʧ��" << endl;
		return;
	}
	Person p;
	ifs.read((char*)&p, sizeof(Person));//��������
	cout << p.m_c << endl << p.m_f << endl;//��������Ա
	ifs.clear();//�ر��ļ�
}
int main()
{
	Test01();
	return 0;
}