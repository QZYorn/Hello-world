#include<iostream>
using namespace std;
#include<string>

class Base
{
public:
	void Title()
	{
		cout << "�����Ǳ��⣡����" << endl;
	}
	void Menu()
	{
		cout << "�����ǲ˵���������" << endl;
	}
	void End()
	{
		cout << "������ҳβ��������������������������" << endl;
	}
};

class Java :public Base//class ���� ���̳з�ʽ ����
{
public:
	void Test()
	{
		cout << "JAVAJAVAJAVAJAVA" << endl;
	}
};
class CPP :public Base
{
public:
	void Test()
	{
		cout << "CPPCPPCPPCPPCPP" << endl;
	}
};
class C :public Base
{
public:
	void Test()
	{
		cout << "CCCCCCCCCCCCCCC" << endl;
	}
};
void Test01()
{
	Java ja;
	ja.Title();//����ɵ��ø���Ȩ�޳�Ա����
	ja.Menu();//�ӻ���̳й���
	ja.Test();//�Լ����ӵĳ�Ա
	ja.End();
	cout << "_____________________________" << endl;
	CPP cp;
	cp.Title();
	cp.Menu();
	cp.Test();
	cp.End();
	cout << "_____________________________" << endl;
	C c;
	c.Title();
	c.Menu();
	c.Test();
	c.End();
	cout << "_____________________________" << endl;
}

int main()
{
	Test01();
	return 0;
}