#include<iostream>
#include<string>
using namespace std;

void Test01()
{
	string str1("abced");
	string str2("abced");
	if (str1.compare(str2) == 0)
	{
		cout << "相等" << endl;
	}
	else
	{
		cout << "不相等" << endl;
	}
}

int main()
{
	Test01();
	system("pause");
	return 0;
}