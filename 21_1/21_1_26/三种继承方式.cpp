#include<iostream>
using namespace std;
#include<string>

class Base
{
public:
	int m_a;
protected:
	int m_b;
private:
	int m_c;
};

class Son1 :public Base//公共继承Base
{
	void func()
	{
		m_a = 100;//公共继承的公共成员依然是 公共成员
		m_b = 100;//公共继承的保护成员依然是 保护成员，子类可以访问
		//m_c = 100;//子类无法访问父类私有权限的成员
	}
};

class Son2 :protected Base//保护继承Base
{
	void func()
	{
		m_a = 100;//保护继承的公共成员会变为 保护成员
		m_b = 100;//保护继承的保护成员依然是 保护成员，子类可以访问
		//m_c = 100;//子类无法访问父类私有权限的成员
	}
};

class Son3 :private Base//私有继承Base
{
	void func()
	{
		m_a = 100;//私有继承的公共成员会变为 私有成员
		m_b = 100;//私有继承的保护成员会变为 私有成员
		//m_c = 100;//子类无法访问父类私有权限的成员
		//私有断子绝孙啊！！
	}
};

class GrandSon2 :public Son2//公共继承Son2
{
	void func()
	{
		m_a = 100;//公共继承的保护成员依然是 保护成员，子类可以访问
		m_b = 100;//公共继承的保护成员依然是 保护成员，子类可以访问
		//m_c = 100;//子类无法访问父类私有权限的成员
	}
};

class GrandSon3 :public Son3//公共继承Son3
{
	void func()
	{
		//m_a = 100;//子类无法访问父类私有权限的成员
		//m_b = 100;//子类无法访问父类私有权限的成员
		//m_c = 100;//子类无法访问父类私有权限的成员
	}
};

void Test01()
{
	Son1 s1;
	s1.m_a = 100;  //公共继承的公共成员依然是 公共成员
	//s1.m_b = 100;//公共继承的保护成员依然是 保护成员，类外无法访问
	//s1.m_c = 100;

	Son2 s2;
	/*s2.m_a = 100;//保护继承的公共成员会变为 保护成员,类外无法访问
	s2.m_b = 100;  //保护继承的保护成员依然是 保护成员,类外无法访问
	s2.m_c = 100;*/

	Son3 s3;
	/*s3.m_a = 100;//私有继承的公共成员会变为 私有成员
	s3.m_b = 100;  //私有继承的保护成员会变为 私有成员
	s3.m_c = 100;*/

	GrandSon2 gs2;
	//s2.m_a = 100;//公共继承的保护成员依然是 保护成员,类外无法访问
	//s2.m_b = 100;//公共继承的保护成员依然是 保护成员,类外无法访问
	//s2.m_c = 100;
}
int main()
{
	Test01();
	return 0;
}