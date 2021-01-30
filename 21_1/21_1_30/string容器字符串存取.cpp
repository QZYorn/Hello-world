#include<iostream>
#include<string>
using namespace std;

void Test01()
{
	string str1("abced");
	for (int i = 0; i < str1.size(); i++)
	{
		cout << str1[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < str1.size(); i++)
	{
		cout << str1.at(i) << " ";
	}
	cout << endl;
	str1[2] = '0';
	cout << str1 << endl;
	str1.at(0) = '0';
	cout << str1 << endl;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}