#include<iostream>
using namespace std;

class Person
{
public:
	static int m_a;//������̬��Ա����

private:
	static int m_b;//˽�о�̬��Ա����

};

int Person::m_a = 100;//��ʼ��
int Person::m_b = 200;
void Test()
{
	Person p1;
	cout << "p1.m_a = " << p1.m_a << endl;
	cout << "p1.m_a = " << Person::m_a << endl;

	Person p2;
	p2.m_a = 1000;//�����Ա
	cout << "p1.m_a = " << p1.m_a << endl;
	cout << "p1.m_a = " << Person::m_a << endl;

	//cout << "p1.m_a = " << Person::m_b << endl;

}
int main()
{
	Test();
	return 0;
}