#include<iostream>
using namespace std;
#include<string>

class Animail
{
public:
	int m_Age;
};
class Sheep :virtual public Animail{};//��virtual���Ϊ��̳У���ʱ�����ĸ���AnimailΪ�����
class Tuo   :virtual public Animail{};//��������Դ�˷�
class SheepTuo :public Sheep, public Tuo{};//���μ̳�


void Test01()
{
	SheepTuo st1;
	//st1.m_Age = 20;//����������
	st1.Sheep::m_Age = 18;
	st1.Tuo::m_Age = 40;
	cout << "Sheep�������� m_Age = " << st1.Sheep::m_Age << endl;
	cout << "Tuo��������   m_Age = " << st1.Tuo::m_Age << endl;//��̳й���һ�����������

}

int main()
{
	Test01();
	return 0;
}