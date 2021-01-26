#include<iostream>
using namespace std;
#include<string>

class Animail
{
public:
	int m_Age;
};
class Sheep :virtual public Animail{};//加virtual后变为虚继承，此时公共的父类Animail为虚基类
class Tuo   :virtual public Animail{};//避免了资源浪费
class SheepTuo :public Sheep, public Tuo{};//菱形继承


void Test01()
{
	SheepTuo st1;
	//st1.m_Age = 20;//产生二义性
	st1.Sheep::m_Age = 18;
	st1.Tuo::m_Age = 40;
	cout << "Sheep作用域下 m_Age = " << st1.Sheep::m_Age << endl;
	cout << "Tuo作用域下   m_Age = " << st1.Tuo::m_Age << endl;//虚继承共享一份虚基类数据

}

int main()
{
	Test01();
	return 0;
}