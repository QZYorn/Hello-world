#include<iostream>
#include<string>
using namespace std;

class Student
{
public:

	//属性
	//姓名
	string name;
	//学号
	string num;

	//行为
	//显示姓名
	void ShowName()
	{
		cout << "学生的姓名为" << name << endl;
	}
	//显示学号
	void ShowNum()
	{
		cout << "学生的学号为" << num << endl;
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

	/*cout << "输入s1的名字" << endl;
	cin >> s1.name;
	cout << "输入s1的学号" << endl;
	cin >> s1.num;*/

	/*cout << "输入s2的名字" << endl;
	cin >> s2.name;
	cout << "输入s2的学号" << endl;
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