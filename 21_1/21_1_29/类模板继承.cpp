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
class Son1 :public Base<int>//父类为类模板时，非类模板子类 继承需指明父类模板参数具体类型
{};

template<class TBase,class TSon>
class Son2 :public Base<TBase>//或者子类也做成类模板，更灵活
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