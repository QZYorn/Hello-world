#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include<assert.h>



void Test01()
{
	ifstream ifs;//创建文件流，读方式
	ifs.open("test.txt", ios::in);//打开文件test.txt,读操作
	if (! ifs.is_open())//判断打开是否成功
	{
		cout << "打开失败" << endl;
		return;
	}
	//第一种方式
	char buf1[1024] = { 0 };
	while (ifs >> buf1)
	{
		cout << buf1 << endl;
	}

	//第二种方式
	while (ifs.getline(buf1, sizeof(buf1)))
	{
		cout << buf1 << endl;
	}

	//第三种方式
	string buf2;
	while (getline(ifs, buf2))
	{
		cout << buf2 << endl;
	}

	//第四种方式
	char c;
	while ((c = ifs.get()) != EOF)
	{
		cout << c;
	}

	ifs.close();//关闭文件
}
int main()
{
	Test01();
	return 0;
}