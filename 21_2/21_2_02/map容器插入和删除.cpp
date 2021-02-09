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
	map<int, int> m;
	m.insert(pair<int, int>(1, 10)); 
	m.insert(make_pair(2, 20));
	m.insert(map<int, int>::value_type(3, 40));
	m[4] = 80;
	printMap(m);

	m.erase(3);//ɾ��keyΪ3��Ԫ��
	printMap(m);

	m.erase(m.begin());//���ݵ�����λ��ɾ��Ԫ��
	printMap(m);

	m.erase(m.begin(), m.end());//ɾ��������Ԫ��
	printMap(m);
	//��Ч
	m.clear();
}

int main()
{
	Test01();
	system("pause");
	return 0;
}