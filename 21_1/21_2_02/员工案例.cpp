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
* ��˾������Ƹ��10��Ա����ABCDEFGHIJ����10��Ա�����빫˾֮����Ҫָ��Ա�����Ǹ����Ź���
* Ա����Ϣ��: ����  ������ɣ����ŷ�Ϊ���߻����������з�
* �����10��Ա�����䲿�ź͹���
* ͨ��multimap������Ϣ�Ĳ���  key(���ű��) value(Ա��)
* �ֲ�����ʾԱ����Ϣ

1. ����10��Ա�����ŵ�vector��
2. ����vector������ȡ��ÿ��Ա���������������
3. ����󣬽�Ա�����ű����Ϊkey������Ա����Ϊvalue�����뵽multimap������
4. �ֲ�����ʾԱ����Ϣ
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
		wk.m_Name = "Ա��";
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
	cout << "�߻���" << endl;
	multimap<int,Worker>::iterator it = mwk.find(CEHUA);
	int count = mwk.count(CEHUA);
	for (int i = 0; i < count; i++)
	{
		cout << "������" << it->second.m_Name << "  ���ʣ�" << it->second.m_Salary << endl;
		it++;
	}
	cout << endl;

	cout << "������" << endl;
	it = mwk.find(MEISHU);
	count = mwk.count(MEISHU);
	for (int i = 0; i < count; i++)
	{
		cout << "������" << it->second.m_Name << "  ���ʣ�" << it->second.m_Salary << endl;
		it++;
	}
	cout << endl;

	cout << "�з���" << endl;
	it = mwk.find(YANFA);
	count = mwk.count(YANFA);
	for (int i = 0; i < count; i++)
	{
		cout << "������" << it->second.m_Name << "  ���ʣ�" << it->second.m_Salary << endl;
		it++;
	}
	cout << endl;

}

void Test01()
{
	srand((unsigned int)time(NULL));
	vector<Worker> vwk;
	creatWorker(vwk);//����10��Ա������vector����
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