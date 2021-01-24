#include<iostream>
#include<string>
using namespace std;

class Person
{
public:
	string getName()//读名字
	{
		return m_name;
	}
	void setName(string name)//写名字
	{
		m_name = name;
	}

	int getAge()//读年龄
	{
		return m_age;
	}
	void setAge(int age)//写年龄
	{
		if (age<0 || age>150)
		{
			cout << "骗鬼呢你" << endl;
			m_age = 0;
			return;
		}
		m_age = age;
	}


	void setLover(string lover)//写情人
	{
		m_lover = lover;
	}


private:
	string m_name = "张三";//名字 可读可写
	int m_age = 18;//年龄 可读 可写
	string m_lover = "琳琳";//情人 可写

};

int main()
{
	Person p1;
	cout << "名字是" << p1.getName() << endl;
	p1.setName("刘丽");
	cout << "修改后名字是" << p1.getName() << endl;
	cout << "年龄是" << p1.getAge() << endl;
	p1.setAge(100);
	p1.setAge(666);
	cout << "修改后年龄是" << p1.getAge() << endl;

	//p1.setAge;
	//p1.m_age = 10;
	p1.setLover("刘玲");
	return 0;
}