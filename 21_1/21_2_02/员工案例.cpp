#include<iostream>
using namespace std;
#include<map>
#include<string>
#include<vector>
#include<time.h>

#define CEHUA 0
#define MEISHU 1
#define YANFA 2
/*
* 公司今天招聘了10个员工（ABCDEFGHIJ），10名员工进入公司之后，需要指派员工在那个部门工作
* 员工信息有: 姓名  工资组成；部门分为：策划、美术、研发
* 随机给10名员工分配部门和工资
* 通过multimap进行信息的插入  key(部门编号) value(员工)
* 分部门显示员工信息

1. 创建10名员工，放到vector中
2. 遍历vector容器，取出每个员工，进行随机分组
3. 分组后，将员工部门编号作为key，具体员工作为value，放入到multimap容器中
4. 分部门显示员工信息
*/
class Worker
{
public:

	string m_Name;
	int m_Salary;
};

void creatWorker(vector<Worker> &vwk)
{
	string nameSeed = "ABCDEFGHIJ";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		Worker wk;
		wk.m_Name = "员工";
		wk.m_Name += nameSeed[i];
		wk.m_Salary = rand() % 10001 + 10000;
		vwk.push_back(wk);
	}
}

void setGroup(multimap<int, Worker> &mwk, vector<Worker> &vwk)
{
	for (vector<Worker>::iterator it = vwk.begin(); it != vwk.end(); it++)
	{
		int group = rand() % 3;
		mwk.insert(make_pair(group, *it));
	}
}

void printWorker(multimap<int, Worker> &mwk)
{
	cout << "策划：" << endl;
	multimap<int,Worker>::iterator it = mwk.find(CEHUA);
	int count = mwk.count(CEHUA);
	for (int i = 0; i < count; i++)
	{
		cout << "姓名：" << it->second.m_Name << "  工资：" << it->second.m_Salary << endl;
		it++;
	}
	cout << endl;

	cout << "美术：" << endl;
	it = mwk.find(MEISHU);
	count = mwk.count(MEISHU);
	for (int i = 0; i < count; i++)
	{
		cout << "姓名：" << it->second.m_Name << "  工资：" << it->second.m_Salary << endl;
		it++;
	}
	cout << endl;

	cout << "研发：" << endl;
	it = mwk.find(YANFA);
	count = mwk.count(YANFA);
	for (int i = 0; i < count; i++)
	{
		cout << "姓名：" << it->second.m_Name << "  工资：" << it->second.m_Salary << endl;
		it++;
	}
	cout << endl;

}

void Test01()
{
	srand((unsigned int)time(NULL));
	vector<Worker> vwk;
	creatWorker(vwk);//创造10个员工塞进vector容器
	multimap<int, Worker> mwk;
	setGroup(mwk,vwk);
	printWorker(mwk);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}