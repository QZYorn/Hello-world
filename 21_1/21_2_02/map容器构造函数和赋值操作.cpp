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
	map<int, int> m;//默认构造
	m.insert(pair<int, int>(1, 10)); 
	m.insert(pair<int, int>(3, 40));
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(4, 80));
	m.insert(pair<int, int>(0, 0));
	//插入时自动排序，不可插入key值重复的元素
	printMap(m);

	map<int, int> m1(m);//拷贝构造
	printMap(m1);

	map<int, int> m2;
	m2 = m1;//赋值操作
	printMap(m2);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}