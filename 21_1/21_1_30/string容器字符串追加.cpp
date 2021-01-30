#include<iostream>
#include<string>
using namespace std;

void Test01()
{
	string str1;
	cout << str1 << endl;

	str1 += "我";
	cout << str1 << endl;

	string str2("喜欢 ");
	str1 += str2;
	cout << str1 << endl;

	str1 += 'G';
	cout << str1 << endl;

	str1.append("ame");
	cout << str1 << endl;

	string str3(":");
	str1.append(str3);
	cout << str1 << endl;

	str1.append("LOL DOTA",4);//把"LOL DOTA"前四个字符追加到str1后
	cout << str1 << endl;

	str1.append("LOLDOTA", 3,4);//从"LOLDOTA"角标为3的字符开始，追加4个字符到str1后
	cout << str1 << endl;

}

int main()
{
	Test01();
	system("pause");
	return 0;
}