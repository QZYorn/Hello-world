#include<iostream>
using namespace std;
#include<string>

class MyAdd
{
public:
	int operator()(int a,int b)//�����з���ֵ�������б�
	{
		return a + b;
	}
};

class MyPrint
{
public:
	MyPrint()
	{
		this->count = 0;
	}
	void operator()(string test)
	{
		cout << test << endl;
		this->count++;
	}
	int count;
};

void Print(MyPrint &mp, string test)
{
	mp(test);
}

void Test01()
{
	MyAdd myadd;
	int sum = myadd(10, 20);//ʹ������������ͨ����һ��
	cout << sum << endl;

	MyPrint myprint;
	myprint("������");
	myprint("������");
	myprint("������");
	myprint("������");
	myprint("������");
	cout << "myprint��ӡ��" << myprint.count << "��" << endl;//���Լ�¼

	Print(myprint, "������");//�ɴ���
}

int main()
{
	Test01();
	system("pause");
	return 0;
}