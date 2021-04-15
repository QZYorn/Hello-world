#define _CRT_SECURE_NO_WARNINGS 1
#define _SCL_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
//#include<iterator>
#include<sstream>
#include<vector>
//#include<list>
//#include<map>
//#include<set>
//#include<deque>
//#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
#include<memory>
//#include<stdlib.h>
#include<tuple>
#include<bitset>
#include<random>
#include<ctime>
#include<iomanip>
#include"Sales_data.h"
using namespace std;
//using namespace std::placeholders;


bool compareIsbn(const Sales_data &s1, const Sales_data &s2)
{
	return s1.isbn() == s2.isbn();
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

//17.11
struct Exam
{
	
	Exam(const unsigned &a) :_answer(a){}
	void change(const unsigned &No, const bool &TN)
	{
		_answer[No - 1] = TN;
	}
	ostream &print(ostream &os)
	{
		return os << _answer << " ";
	}
	bitset<100> _answer;
};

unsigned my_random(const unsigned &seed, const unsigned &min, const unsigned &max)
{
	static default_random_engine e(seed);//随机数引擎
	static uniform_int_distribution<unsigned> u(min, max);//随机数分布器
	default_random_engine::result_type i = u(e);
	return i;
}

void test17()
{
	//17.1.1
	cout << ">>>>>>>>>-----  17.1.1  -----<<<<<<<<<" << endl;
	//17.1
	tuple<int, int, int> iii(10, 20, 30);
	//17.2
	tuple<string, vector<string>, pair<string, int>> svp;
	//17.9
	string bstr;
	//cin >> bstr;
	bitset<8> bv(bstr);
	//cout << bv << endl;

	//17.10
	bitset<22> bv21;
	bv21.set(1);
	bv21.set(2);
	bv21.set(3);
	bv21.set(5);
	bv21.set(8);
	bv21.set(13);
	bv21.set(21);

	//17.13
	unsigned a = 1<<1|1<<2|1<<3;
	Exam ax(a);
	ax.change(5,true);
	ax.print(cout);

	//17.28
	cout << endl;
	cout << my_random(time(0), 0, 15);

	//正态分布200个数在(4,1.5) 均值4 标准差1.5 情况下分布情况 
	default_random_engine e(time(0));
	normal_distribution<> n(4, 1.5);
	vector<unsigned> vals(9);//九个元素默认为0
	for (size_t i = 0; i != 200; ++i)
	{
		unsigned v = lround(n(e));//舍入到最近的整数
		if (v < vals.size())//限定结果在范围内
			++vals[v];//统计每个数出现次数
	}
	cout << endl;
	for (size_t i = 0; i != vals.size(); ++i)
	{
		cout << i << "：" << string(vals[i], '*') << endl;
	}

	//17.34
	int i = -16;
	double d = 3.14159;
	cout << boolalpha
		<< true << " "
		<< false << noboolalpha << endl;
	cout << showbase
		<< hex << "hex："
		<< "i：" << i << " "
		<< "\td：" << d << endl
		<< oct << "oct："
		<< "i：" << i << " "
		<< "\td：" << d << dec << noshowbase << endl;
	cout << showbase << uppercase
		<< hex << "hex："
		<< "i：" << i << " "
		<< "\td：" << d << endl
		<< oct << "oct："
		<< "i：" << i << " "
		<< "\td：" << d << dec << noshowbase << endl;
	cout << showbase << showpos //显示进制前缀，显示正号
		<< hexfloat << "hex：" << left << setfill('#')//左对齐,空格变为填充#
		<< "i：" << setw(10) << i << " "
		<< "d：" << setw(10) << d << endl
		<< fixed << "fix：" << right << setfill(' ')//右对齐，填充#变为空格
		<< "i：" << setw(10) << i << " "
		<< "d：" << setw(10) << d << endl
		<< scientific << "sci：" << setprecision(3)<< internal//浮点数精度调为3，符号与值之间填充空格
		<< "i：" << setw(10) << i << ends
		<< "d：" << setw(10) << d <<endl
		<< defaultfloat << "bin：" << setbase(16)//整数以16进制输出
		<< "i：" << setw(10) << i << " "
		<< "d：" << setw(10) << d  << noshowbase << noshowpos << endl;

	//17.37
	cout << endl;
	ifstream ifs("test.txt",fstream::in);
	if (!ifs.is_open())
	{
		cout << "error open file" << endl;
		return ;
	}
	vector<string> vs;
	char arr[20] = {};
	int ch = 0;
	while (ifs.getline(arr,20,'\n').good())
	{
		vs.push_back(string(arr));
	}
	ifs.close();

	//17.39
	fstream fs("seek.txt", fstream::ate | fstream::in | fstream::out);//定位文件尾以及读写的方式打开
	if (!fs.is_open())
	{
		cout << "error open seek.txt" << endl;
		return;
	}
	auto f_end = fs.tellp();//记录文件尾绝对位置
	fs.seekp(0,fstream::beg);//重定位回文件首
	size_t count = 0;//每行的字节累加器
	string line;//保存当前读取行
	while (fs.good() && fs.tellp() != f_end && getline(fs, line))//当前位置不为原文件尾  并且(然后) 读取下一行 并且 文件流不出错
	{
		count += line.size() + 1;//累加器加上每一行长度 以及 1位换行符
		auto f_cur = fs.tellp();//记录文件流当前位置
		fs.seekp(0, fstream::end);//定位到文件尾
		fs << count;//在文件尾输入当前字节数
		if (f_cur != f_end)//若原文件流位置 不为 原文件尾
			fs << " ";//输入空格
		fs.seekp(f_cur);//文件流定位回原位置
	}
	fs.seekp(0, fstream::end);//定位到文件尾
	fs << '\n';//输入一个换行符
	fs.close();
}

int main()
{
	test17();
	return 0;
}