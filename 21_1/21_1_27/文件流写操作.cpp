#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include<assert.h>



void Test01()
{
	ofstream ofs;//�����ļ�������д����
	ofs.open("test.txt", ios::out);//��text.txt, ��д�ķ�ʽ
	ofs << "jiejiejie" <<endl;
	ofs << "�� �� �� ��������" << endl;
	ofs << "����������������������������������������" << endl;
	ofs.close();
}
int main()
{
	Test01();
	return 0;
}