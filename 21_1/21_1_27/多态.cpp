#include<iostream>
using namespace std;

class Animail
{
public:
	void Eat()
	{
		cout << "动物在吃" << endl;
	}

	virtual void Speak()//加上virtual关键字变虚函数
	{
		cout << "动物在叫" << endl;
	}
};

class Cat:public Animail
{
public:
	//在编译阶段就确定函数地址，静态联编
	void Eat()
	{
		cout << "猫在吃" << endl;
	}

	//在运行阶段才确认函数地址，动态联编
	void Speak()//函数重写，与父类虚函数同名，参数列表相同，返回值相同
	{
		cout << "猫在叫" << endl;
	}
};
void WhoEat(Animail &animail)
{
	animail.Eat();
}
void WhoSpeak(Animail &animail)//多态发生条件：需由父类指针或引用指向虚函数
{
	animail.Speak();
}
void Test01()
{
	Cat c1;
	WhoEat(c1);
	WhoSpeak(c1);
}

int main()
{
	Test01();
	return 0;
}