#include<iostream>
#include<string>
using namespace std;

void Test01()
{
	string str1;
	cout << str1 << endl;

	str1 += "��";
	cout << str1 << endl;

	string str2("ϲ�� ");
	str1 += str2;
	cout << str1 << endl;

	str1 += 'G';
	cout << str1 << endl;

	str1.append("ame");
	cout << str1 << endl;

	string str3(":");
	str1.append(str3);
	cout << str1 << endl;

	str1.append("LOL DOTA",4);//��"LOL DOTA"ǰ�ĸ��ַ�׷�ӵ�str1��
	cout << str1 << endl;

	str1.append("LOLDOTA", 3,4);//��"LOLDOTA"�Ǳ�Ϊ3���ַ���ʼ��׷��4���ַ���str1��
	cout << str1 << endl;

}

int main()
{
	Test01();
	system("pause");
	return 0;
}