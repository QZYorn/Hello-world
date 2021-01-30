#include<iostream>
#include<string>
using namespace std;

void Test01()
{
	string str1("abcde");
	string  str2 = str1.substr(0,3);
	cout << str2 << endl;

	str1 = "86423948888@154.com";
	int pos = str1.find('@');
	str2 = str1.substr(0, pos);
	cout << str2 << endl;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}