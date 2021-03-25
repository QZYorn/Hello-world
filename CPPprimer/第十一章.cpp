#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
//#include<iterator>
#include<sstream>
#include<vector>
#include<list>
#include<map>
#include<deque>
#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
using namespace std;
using namespace std::placeholders;

void test11_1()
{
	cout << "\n11.1" << endl;
	
	//11.3
	string words;
	map<string, int> msi;
	while (cin >> words)
	{
		for (auto it = words.begin(); it < words.end(); ++it)
		{
			if (ispunct(*it))
			{
				auto f = words.find(*it);
				words.erase(f,1);
			}

			*it = tolower(*it);
		}
		++msi[words];
	}

	for (const auto &wPair : msi)
		cout << wPair.first << " occurs " << wPair.second << ((wPair.second > 1) ? " times" : " time") << endl;


}

void test11_2_1()
{
	cout << "\n11.2.1" << endl;

	//11.7
	map<string, vector<string>> home;
	string family;
	string children;
	cin.clear();

	while (cin >> family && getline(cin,children))
	{
		auto posPr = 1;
		auto posCu = posPr;
		while (posCu < children.size())
		{
			if (children[posCu] == ' ')
			{
				home[family].push_back(children.substr(posPr, posCu));
				++posCu;
				posPr = posCu;
			}
			++posCu;
		}
	}


}

void test11_2_2()
{
	cout << "\n11.2.2" << endl;

	//11.9
	map<string, list<int>> word_line;

}

void test11_2_3()
{
	cout << "\n11.2.3" << endl;

	//11.12 & 11.13
	vector<pair<string, int>> pvec;
	string str;
	int i;
	while (cin >> str && cin >> i)
	{
		//pvec.push_back({ str, i });
		//pvec.push_back(make_pair(str, i));
		pair<string, int> p{ str, i };
		pvec.push_back(p);
	}

}

void test11_3_1()
{
	cout << "\n11.3.1" << endl;

	//11.16
	map<int, int> m;
	auto it = m.begin();
	it->second = 5;

	//11.17
	map<string, int> map_it;
	map<string, int>::iterator mit = map_it.begin();
	auto mit2 = map_it.begin();
}

int main()
{
	//test11_1();
	//test11_2_1();
	//test11_2_2();
	//test11_2_3();
	test11_3_1();
	return 0;
}