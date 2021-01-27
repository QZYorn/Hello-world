#include<iostream>
using namespace std;
#include<string>
class Calculater//��ͨ��ʽʵ�ּ�����
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

//��̬�ŵ�
//1.��֯�ṹ����
//2.����ά��
//3.�ɶ���ǿ
class AbstractCaculator//�����������
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

void Test01()//��ͨ��ʽʵ�ּ�����
{
	Calculater c1;
	c1.m_a = 100;
	c1.m_b = 100;
	cout << c1.m_a << " + " << c1.m_b << "=" << c1.GetResult("+") << endl;
	cout << c1.m_a << " - " << c1.m_b << "=" << c1.GetResult("-") << endl;
	cout << c1.m_a << " * " << c1.m_b << "=" << c1.GetResult("*") << endl;

}

void Test02()//��̬��ʽʵ�ּ�����
{
	//��̬��������������ָ�������ָ������
	AbstractCaculator *abc = new Add;
	abc->m_a = 100;
	abc->m_b = 100;
	cout << abc->m_a << " + " << abc->m_b << " = " << abc->GetResult() << endl;
	delete abc;//ʹ��������
	abc = NULL;//�ÿ�

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