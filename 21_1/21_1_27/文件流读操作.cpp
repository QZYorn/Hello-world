#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include<assert.h>



void Test01()
{
	ifstream ifs;//�����ļ���������ʽ
	ifs.open("test.txt", ios::in);//���ļ�test.txt,������
	if (! ifs.is_open())//�жϴ��Ƿ�ɹ�
	{
		cout << "��ʧ��" << endl;
		return;
	}
	//��һ�ַ�ʽ
	char buf1[1024] = { 0 };
	while (ifs >> buf1)
	{
		cout << buf1 << endl;
	}

	//�ڶ��ַ�ʽ
	while (ifs.getline(buf1, sizeof(buf1)))
	{
		cout << buf1 << endl;
	}

	//�����ַ�ʽ
	string buf2;
	while (getline(ifs, buf2))
	{
		cout << buf2 << endl;
	}

	//�����ַ�ʽ
	char c;
	while ((c = ifs.get()) != EOF)
	{
		cout << c;
	}

	ifs.close();//�ر��ļ�
}
int main()
{
	Test01();
	return 0;
}