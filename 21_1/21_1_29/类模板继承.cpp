#include<iostream>
using namespace std;
#include<string>

template<class T>
class Base
{
public:

	T m_base;
};

//class Son1:public Base
class Son1 :public Base<int>//����Ϊ��ģ��ʱ������ģ������ �̳���ָ������ģ�������������
{};

template<class TBase,class TSon>
class Son2 :public Base<TBase>//��������Ҳ������ģ�壬�����
{
public:

	TSon m_son;
};

void Test01()
{
	Son1 s1;
	Son2<string,int> s2;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}