#include<iostream>
using namespace std;

class Person
{
public:

	void static func()
	{
		cout << "void static func() " << endl;
		m_a = 999;//�ɷ��ʾ�̬��Ա����
		m_b = 666;
		//m_c = 111;//���ɷ��ʷǾ�̬��Ա����
	}

	static int m_a;//������̬����

private:
	void static func2()
	{
		cout << "void static func() " << endl;
		m_a = 999;//�ɷ��ʾ�̬��Ա����
		m_b = 666;
		//m_c = 111;//���ɷ��ʷǾ�̬��Ա����
	}

	static int m_b;//˽�о�̬����
	int m_c;
};

int Person::m_a = 100;//��ʼ��
int Person::m_b = 200;
void Test()
{
	Person p1;
	p1.func();//ͨ���������
	Person::func();//ͨ����������
	//p1.func2();//����Ȩ������
	//Person::func2();//
	//cout << "p1.m_a = " << Person::m_b << endl;//����Ȩ������

}
int main()
{
	Test();
	return 0;
}