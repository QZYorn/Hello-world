#include<iostream>
using namespace std;
#include<map>
void printMap(map<int, int> &m)
{
	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key:" << it->first << "  value:" << (*it).second << endl;
	}
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
	printMap(m);

	map<int, int> m1(m);//��������
	printMap(m1);

	map<int, int> m2;
	m2 = m1;//��ֵ����
	printMap(m2);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}