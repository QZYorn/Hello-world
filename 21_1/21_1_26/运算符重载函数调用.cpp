#include<iostream>
using namespace std;
#include<string>

class MyPrint
{
public:
	//�����() ������
	void operator()(string str)//������������� ����
	{
		cout << str << endl;
	}
};

class MyAdd
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}
};

void Test01()
{
	MyPrint mp;
	mp("jiejiejie");//�º���
	mp.operator()("jiejiejie");//������������� ���� ��ʵ��
}

void Test02()
{
	MyAdd ma;
	int ret = ma(10, 50);
	ret = ma.operator()(10, 50);//������������� ���� ��ʵ��
	cout << ret << endl;
	cout << MyAdd()(50, 50) << endl;//��������ֱ�ӵ��ó�Ա����
}

int main()
{
	Test01();
	Test02();
	return 0;
}