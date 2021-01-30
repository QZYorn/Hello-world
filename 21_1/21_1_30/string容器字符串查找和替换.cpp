#include<iostream>
#include<string>
using namespace std;

void Test01()
{
	string str1;
	str1.assign("abcdefgdedede");
	cout << str1 << endl;

	int ret = str1.find("de");//从左往右查找，起始位置0，，返回角标
	cout << "ret = " << ret << endl;//3

	ret = str1.rfind("de");//从右往左查找，起始位置0，返回角标
	cout << "ret = " << ret << endl;//11

	ret = str1.rfind("de",4);//从右往左查找，起始位置4，返回角标
	cout << "ret = " << ret << endl;//3

	str1.replace(2, 1, "111");//起始位置2'c',一个字符替换成"111"
	cout << str1 << endl;// 即abcde ->  ab111de,  c被替换成111

}

int main()
{
	Test01();
	system("pause");
	return 0;
}