#include<iostream>
using namespace std;
#include<string>
#include<assert.h>

class Base
{
public:
	Base()
	{
		cout << "Base���캯������" << endl;
	}
	//virtual ~Base()//������������������ڴ濪���ڶ���ʱ������ָ��ָ����������ͷ�ʱ�޷�����������������������
	//{
	//	cout << "Base������������" << endl;
	//}
	virtual ~Base() = 0;//������������������������ʵ�֡�
};

Base::~Base()//��Ȼ��Ҫ�о���ʵ��
{
	cout << "Base����������������" << endl;
}

class Son :public Base
{
public:
	Son(string name)
	{
		cout << "Son���캯��҅��" << endl;
		m_Name = new string(name);
	}

	~Son()
	{
		cout << "Son��������҅��" << endl;
		assert(m_Name != NULL);
		delete m_Name;
		m_Name = NULL;
	}
	string *m_Name;
};

void Test01()
{
	Base *b = new Son("wangwu");
	delete b;
	b = NULL;
	//Base b;//�д���������������Ϊ�����࣬�޷�ʵ����
}
int main()
{
	Test01();
	return 0;
}