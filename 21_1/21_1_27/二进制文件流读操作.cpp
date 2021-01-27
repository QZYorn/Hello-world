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
	ifstream ifs("Person.txt", ios::in | ios::binary);//创建输入流对象，读|二进制方式打开
	if (!ifs.is_open())//判断打开是否成功
	{
		cout << "打开失败" << endl;
		return;
	}
	Person p;
	ifs.read((char*)&p, sizeof(Person));//读出操作
	cout << p.m_c << endl << p.m_f << endl;//输出对象成员
	ifs.clear();//关闭文件
}
int main()
{
	Test01();
	return 0;
}