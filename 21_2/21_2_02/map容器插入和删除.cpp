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

	m.erase(3);//删除key为3的元素
	printMap(m);

	m.erase(m.begin());//根据迭代器位置删除元素
	printMap(m);

	m.erase(m.begin(), m.end());//删除区间内元素
	printMap(m);
	//等效
	m.clear();
}

int main()
{
	Test01();
	system("pause");
	return 0;
}