#define _CRT_SECURE_NO_WARNINGS 1
#define _SCL_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
//#include<fstream>
//#include<iterator>
#include<sstream>
#include<vector>
#include<list>
#include<map>
#include<set>
//#include<deque>
//#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
#include<memory>
//#include<stdlib.h>
#include<tuple>
#include"Sales_data.h"
using namespace std;
//using namespace std::placeholders;


bool compareIsbn(const Sales_data &s1, const Sales_data &s2)
{
	return s1.isbn() == s2.isbn();
}
ostream& operator<<(ostream& os, const Sales_data& s_data)
{
	os << s_data.isbn() << " " << s_data.units_sold << " "
		<< s_data.revenue << " " << s_data.avg_price();
	return os;
}

//17.4
//matches三个成员：书店的索引，两个指向书店vector中元素的迭代器
typedef	tuple<vector<Sales_data>::size_type,
			  vector<Sales_data>::const_iterator,
			  vector<Sales_data>::const_iterator> matches;
//files保存每家店的销售记录
//findBook返回一个vector,其中每一个成员都是销售了给定书籍的一家书店
vector<matches> 
findBook(const vector<vector<Sales_data>> &files,
		 const string &book)
{
	vector<matches> ret;
	for (auto it = files.cbegin(); it != files.cend(); ++it)//每一家书店
	{
		auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);//与每本书的ISBN比较并返回范围
		if (found.first != found.second)
			ret.push_back(make_tuple(it - files.cbegin(), found.first, found.second));
	}
	return ret;
}

void reportResult(istream &is, ostream &os, const vector<vector<Sales_data>> &files)
{
	string s;
	while (is >> s)
	{
		auto trans = findBook(files, s);
		if (trans.empty())
		{
			cout << s << " not found in any stores" << endl;
			continue;
		}
		for (const auto &store : trans)//遍历其中每一家店
		{
			os << "store " << get<0>(store) << " sales: "
			   << accumulate(get<1>(store), get<2>(store), Sales_data(s)) << endl;
		}
	}
}

//17.5
typedef	pair<vector<Sales_data>::size_type,pair<
	vector<Sales_data>::const_iterator,
	vector<Sales_data>::const_iterator>> matches2;
vector<matches2>
findBook2(const vector<vector<Sales_data>> &files,
const string &book)
{
	vector<matches2> ret;
	for (auto it = files.cbegin(); it != files.cend(); ++it)//每一家书店
	{
		auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);//与每本书的ISBN比较并返回范围
		if (found.first != found.second)
			ret.push_back(make_pair(it - files.cbegin(),make_pair(found.first, found.second)));
	}
	return ret;
}

//17.6
struct matches3
{
	vector<Sales_data>::size_type sz;
	vector<Sales_data>::const_iterator beg;
	vector<Sales_data>::const_iterator end;
};
vector<matches3>
findBook3(const vector<vector<Sales_data>> &files,
const string &book)
{
	vector<matches3> ret;
	for (auto it = files.cbegin(); it != files.cend(); ++it)//每一家书店
	{
		auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);//与每本书的ISBN比较并返回范围
		if (found.first != found.second)
			ret.push_back(matches3{ it - files.cbegin(), found.first, found.second });
	}
	return ret;
}

void test17()
{
	//17.1.1
	cout << ">>>>>>>>>-----  17.1.1  -----<<<<<<<<<" << endl;
	//17.1
	tuple<int, int, int> iii(10, 20, 30);
	//17.2
	tuple<string, vector<string>, pair<string, int>> svp;
	//17.3

}

int main()
{
	test17();
	return 0;
}