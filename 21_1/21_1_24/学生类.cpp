#include<iostream>
#include<string>
using namespace std;

class Student
{
public:

	//����
	//����
	string name;
	//ѧ��
	string num;

	//��Ϊ
	//��ʾ����
	void ShowName()
	{
		cout << "ѧ��������Ϊ" << name << endl;
	}
	//��ʾѧ��
	void ShowNum()
	{
		cout << "ѧ����ѧ��Ϊ" << num << endl;
	}
	void SetName(string s_name)
	{
		name = s_name;
	}
	void SetNum(string s_num)
	{
		num = s_num;
	}
};

int main()
{
	Student s1;
	Student s2;

	/*cout << "����s1������" << endl;
	cin >> s1.name;
	cout << "����s1��ѧ��" << endl;
	cin >> s1.num;*/

	/*cout << "����s2������" << endl;
	cin >> s2.name;
	cout << "����s2��ѧ��" << endl;
	cin >> s2.num;*/
	s1.SetName("wangwu");
	s1.SetNum("666");
	s2.SetName("lisi");
	s2.SetNum("999");


	s1.ShowName();
	s1.ShowNum();
	s2.ShowName();
	s2.ShowNum();
	return 0;
}