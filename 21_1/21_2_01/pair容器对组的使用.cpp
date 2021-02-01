#include<iostream>
using namespace std;
#include<set>
#include<string>

void printSet(set<int> &s)
{
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void Test01()
{
	pair<string, int> p("ËïÎò¿Õ", 999);
	cout << "ĞÕÃû£º" << p.first << "  ÄêÁä£º" << p.second << endl;

	p = make_pair("Öí°Ë½ä", 582);
	cout << "ĞÕÃû£º" << p.first << "  ÄêÁä£º" << p.second << endl;

}

int main()
{
	Test01();
	system("pause");
	return 0;
}