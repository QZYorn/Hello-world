#include<iostream>
using namespace std;

class Base
{
public:
	//ֻҪ��һ�����麯���������Ϊ������
	virtual void func() = 0;//���麯��
	int m_a;
};

class Son1 :public Base
{
public:
	int m_s1;
};

class Son2 :public Base
{
public:
	void func()
	{
		cout << "jiejiejie" << endl;
	}
	int m_s2;
};

void Test01()
{
	//Base b;//�����಻��ʵ����
	//new Base;
	//Son1 s1;//����������д���ി�麯����������ҲΪ�����࣬����ʵ����
	Base *b = NULL;
	//b = new Base;
	b = new Son2;
	b->func();
	b->m_a = 100;
	delete b;
}



int main()
{
	Test01();
	return 0;
}