#include<iostream>
using namespace std;

int Addi(int a, int b)
{
	return a + b;
}

template<typename T>
T AddT(T a, T b)//����ģ��
{
	return a + b;
}

void Test01()
{
	int a = 10;
	int b = 20;
	char c = 'c';
	cout << Addi(a, b) << endl;
	cout << Addi(a, c) << endl;//������ʽ����ת�����ַ�'c'ת��Ϊ����ASCII��ֵ99

	cout << AddT(a, b) << endl;//�Զ������Ƶ� ,int
	//cout << AddT(a, c) << endl;//��������ʽ����ת��
	cout << AddT<int>(a, c) << endl;//��ʾָ������int��������ʽ����ת��
	cout << AddT<char>(a, c) << endl;//��ʾָ������char��������ʽ����ת��

}



int main()
{
	Test01();
	system("pause");
	return 0;
}