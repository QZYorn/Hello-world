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
	//���������������д|�����Ƶķ�ʽ��
	ofstream ofs("Person.txt", ios::out | ios::binary);
	Person p1 = { "����", 9.99 };
	ofs.write((const char*)&p1, sizeof(Person));
	ofs.close();
}
int main()
{
	Test01();
	return 0;
}