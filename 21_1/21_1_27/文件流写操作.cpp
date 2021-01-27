#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include<assert.h>



void Test01()
{
	ofstream ofs;//创建文件流对象，写操作
	ofs.open("test.txt", ios::out);//打开text.txt, 以写的方式
	ofs << "jiejiejie" <<endl;
	ofs << "我 就 是 ！！！！" << endl;
	ofs << "神神神神神神神神神神神神神神神神神神神神" << endl;
	ofs.close();
}
int main()
{
	Test01();
	return 0;
}