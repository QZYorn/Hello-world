#include<iostream>
using namespace std;
#include<string>

class Base
{
public:
	Base()
	{
		cout << "Base���캯��" << endl;
	}
	~Base()
	{
		cout << "Base��������" << endl;
	}
};
class Son:public Base
{
public:
	Son()
	{
		cout << "Son���캯��" << endl;
	}
	~Son()
	{
		cout << "Son��������" << endl;
	}
};

void Test01()
{
	Son s1;//�̳��У�������ù��캯��ǰ���ȵ��ø��๹�캯������������˳���෴
}

int main()
{
	Test01();
	return 0;
}