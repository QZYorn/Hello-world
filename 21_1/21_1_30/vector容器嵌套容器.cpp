#include<iostream>
#include<string>
using namespace std;
#include<vector>

void Test01()
{
	vector<int> p1;
	vector<int> p2;
	vector<int> p3;
	vector<int> p4;
	vector<int> p5;
	for (int i = 0; i < 6; i++)
	{
		p1.push_back(i);
		p2.push_back(i+1);
		p3.push_back(i+2);
		p4.push_back(i+3);
		p5.push_back(i+4);
	}
	vector<vector<int>> pp;
	pp.push_back(p1);
	pp.push_back(p2);
	pp.push_back(p3);
	pp.push_back(p4);
	pp.push_back(p5);

	for (vector<vector<int>>::iterator it = pp.begin(); it != pp.end(); it++)
	{
		for (vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); vit++)
		{
			cout << *vit << " ";
		}
		cout << endl;
	}
}

int main()
{
	Test01();
	system("pause");
	return 0;
}