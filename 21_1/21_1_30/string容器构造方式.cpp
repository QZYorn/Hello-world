#include<iostream>
#include<string>
using namespace std;

void Test01()
{
	string str1; //Ĭ�Ϲ���
	const char* c = "abcde";
	string str2(c);//����char*
	string str3(str2);//��������
	string str4(10, 'a');
	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;
	cout << str4 << endl;

}

int main()
{
	Test01();
	system("pause");
	return 0;
}