#include<iostream>
using namespace std;

class Animail
{
public:
	void Eat()
	{
		cout << "�����ڳ�" << endl;
	}

	virtual void Speak()//����virtual�ؼ��ֱ��麯��
	{
		cout << "�����ڽ�" << endl;
	}
};

class Cat:public Animail
{
public:
	//�ڱ���׶ξ�ȷ��������ַ����̬����
	void Eat()
	{
		cout << "è�ڳ�" << endl;
	}

	//�����н׶β�ȷ�Ϻ�����ַ����̬����
	void Speak()//������д���븸���麯��ͬ���������б���ͬ������ֵ��ͬ
	{
		cout << "è�ڽ�" << endl;
	}
};
void WhoEat(Animail &animail)
{
	animail.Eat();
}
void WhoSpeak(Animail &animail)//��̬�������������ɸ���ָ�������ָ���麯��
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