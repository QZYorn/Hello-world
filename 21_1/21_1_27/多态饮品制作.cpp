#include<iostream>
using namespace std;

class Drink//��Ʒ������
{
public:
	//��ˮ
	virtual void Boil() = 0;

	//����
	virtual void Brew() = 0;

	//����
	virtual void PowlOut() = 0;

	//����
	virtual void PutIn() = 0;

	void MakeDrink()
	{
		cout << "������..." << endl;
		Boil();
		Brew();
		PowlOut();
		PutIn();
		cout << "������ɣ���" << endl;
	}
};

class Coffee :public Drink//��������
{
public:
	//��ˮ
	virtual void Boil()
	{
		cout << "ʹ���ϵȵ�ţ��" << endl;
	}

	//����
	virtual void Brew()
	{
		cout << "���뿧�Ȼ���" << endl;
	}

	//����
	virtual void PowlOut()
	{
		cout << "������˱���"<< endl;
	}

	//����
	virtual void PutIn()
	{
		cout << "�����������Ǻ�����" << endl;
	}
};

class Cup:public Drink//������
{
public:
	//��ˮ
	virtual void Boil()
	{
		cout << "ʹ�ø�ɽ����ˮ" << endl;
	}

	//����
	virtual void Brew()
	{
		cout << "����������Ҷ" << endl;
	}

	//����
	virtual void PowlOut()
	{
		cout << "����豭��" << endl;
	}

	//����
	virtual void PutIn()
	{
		cout << "�����������" << endl;
	}
};

void doWork(Drink* d)//�ȼ� Drink* d = new xxxxx
{
	d->MakeDrink();
	delete d;//�ͷ�
}

void Test01()
{
	doWork(new Coffee);//���������ڴ棬�������������ָ��
	cout << "-------------" << endl;
	doWork(new Cup);
}

int main()
{
	Test01();
	return 0;
}