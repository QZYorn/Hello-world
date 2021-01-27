#include<iostream>
using namespace std;
#include<string>
class Calculater//普通方式实现计算器
{
public:

	int GetResult(string oper)
	{
		if (oper == "+")
		{
			return m_a + m_b;
		}
		else if (oper == "-")
		{
			return m_a - m_b;
		}
		else if (oper == "*")
		{
			return m_a * m_b;
		}
	}

	int m_a;
	int m_b;
};

//多态优点
//1.组织结构清晰
//2.利于维护
//3.可读性强
class AbstractCaculator//抽象计算器类
{
public:

	virtual int GetResult()
	{
		return 0;
	}

	int m_a; 
	int m_b;
};

class Add :public AbstractCaculator
{
public:
	int GetResult()
	{
		return m_a + m_b;
	}
};
class Sub :public AbstractCaculator
{
public:
	int GetResult()
	{
		return m_a - m_b;
	}
};
class Mul :public AbstractCaculator
{
public:
	int GetResult()
	{
		return m_a * m_b;
	}
};

void Test01()//普通方式实现计算器
{
	Calculater c1;
	c1.m_a = 100;
	c1.m_b = 100;
	cout << c1.m_a << " + " << c1.m_b << "=" << c1.GetResult("+") << endl;
	cout << c1.m_a << " - " << c1.m_b << "=" << c1.GetResult("-") << endl;
	cout << c1.m_a << " * " << c1.m_b << "=" << c1.GetResult("*") << endl;

}

void Test02()//多态方式实现计算器
{
	//多态发生条件，父类指针或引用指向子类
	AbstractCaculator *abc = new Add;
	abc->m_a = 100;
	abc->m_b = 100;
	cout << abc->m_a << " + " << abc->m_b << " = " << abc->GetResult() << endl;
	delete abc;//使用完销毁
	abc = NULL;//置空

	abc = new Sub;
	abc->m_a = 100;
	abc->m_b = 100;
	cout << abc->m_a << " - " << abc->m_b << " = " << abc->GetResult() << endl;
	delete abc;
	abc = NULL;

	abc = new Mul;
	abc->m_a = 100;
	abc->m_b = 100;
	cout << abc->m_a << " * " << abc->m_b << " = " << abc->GetResult() << endl;
	delete abc;
	abc = NULL;
}

int main()
{
	Test01();
	Test02();
	return 0;
}