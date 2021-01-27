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
	//创建输出流对象，以写|二进制的方式打开
	ofstream ofs("Person.txt", ios::out | ios::binary);
	Person p1 = { "李四", 9.99 };
	ofs.write((const char*)&p1, sizeof(Person));
	ofs.close();
}
int main()
{
	Test01();
	return 0;
}