#include<iostream>
using namespace std;

void  Add(int a, int b)
{
	cout << "����" << a + b << endl;
}

template<typename T>
void Add(T a, T b)//����ģ��
{
	cout << "����ģ��" << a + b << endl;
}

template<typename T>
void Add(T a, T b, T c)//����ģ�巢����������
{
	cout << "����ģ������" << a+b+c << endl;
}

void Test01()
{
	int a = 10;
	int b = 20;
	int c = 30;
	char d = 'd';
	char e = 'e';
	Add(a, b);//���ȵ�����ͨ����
	Add<>(a, b);//ʹ�ÿ�ģ������б�ǿ�Ƶ��ú���ģ��
	Add(a, b, c);//��������ģ������
	Add(d, e);//��ģ���ƥ�䣬�����ȵ��ú���ģ��
	Add(a, e);//������̫ƥ�䣬����Ȼ���ȵ�����ͨ����
}



int main()
{
	Test01();
	system("pause");
	return 0;
}