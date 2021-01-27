#include<iostream>
using namespace std;
#include<string>
#include<assert.h>

class Base
{
public:
	Base()
	{
		cout << "Base构造函数调用" << endl;
	}
	//virtual ~Base()//虚析构，解决当子类内存开辟在堆区时，父类指针指向子类对象，释放时无法调用子类析构函数的问题
	//{
	//	cout << "Base析构函数调用" << endl;
	//}
	virtual ~Base() = 0;//纯虚析构，类内声明，类外实现。
};

Base::~Base()//依然需要有具体实现
{
	cout << "Base纯虚析构函数调用" << endl;
}

class Son :public Base
{
public:
	Son(string name)
	{
		cout << "Son构造函数覅用" << endl;
		m_Name = new string(name);
	}

	~Son()
	{
		cout << "Son析构函数覅用" << endl;
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
	//Base b;//有纯虚析构函数的类为抽象类，无法实例化
}
int main()
{
	Test01();
	return 0;
}