#include<iostream>
#include<string>
using namespace std;

void Test01()
{
	string str1("hello");
	str1.insert(1, "EE");//��λ��1�������ַ���
	cout << str1 << endl;

	str1.insert(2, 5, 'E');//��λ��2������5���ַ�
	cout << str1 << endl;

	str1.erase(1, 7);//��λ��1��ɾȥ7���ַ�
	cout << str1 << endl;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}