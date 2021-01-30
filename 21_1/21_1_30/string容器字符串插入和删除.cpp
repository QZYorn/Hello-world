#include<iostream>
#include<string>
using namespace std;

void Test01()
{
	string str1("hello");
	str1.insert(1, "EE");//在位置1处插入字符串
	cout << str1 << endl;

	str1.insert(2, 5, 'E');//在位置2处插入5个字符
	cout << str1 << endl;

	str1.erase(1, 7);//在位置1处删去7个字符
	cout << str1 << endl;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}