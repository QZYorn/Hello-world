#include<iostream>
using namespace std;
#include<map>
void printMap(map<int, int> &m)
{
	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key:" << it->first << "  value:" << (*it).second << endl;
	}
	cout << endl;
}

void Test01()
{
	map<int, int> m;//Ĭ�Ϲ���
	m.insert(pair<int, int>(1, 10)); 
	m.insert(pair<int, int>(3, 40));
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(4, 80));
	m.insert(pair<int, int>(0, 0));
	//����ʱ�Զ����򣬲��ɲ���keyֵ�ظ���Ԫ��
	cout << "����ǰ��" << endl;
	printMap(m);

	map<int, int> m1;
	m1.insert(pair<int, int>(4, 100));
	m1.insert(pair<int, int>(5, 600));
	m1.insert(pair<int, int>(6, 800));
	m1.insert(pair<int, int>(7, 900));
	m1.insert(pair<int, int>(8, 1000));
	printMap(m1);

	if (m.empty())
	{
		cout << "Ϊ��" << endl;
	}
	else
	{
		cout << "��СΪ��" << m.size() << endl;
	}
	m.swap(m1);
	cout << "������" << endl;
	printMap(m);
	printMap(m1);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}