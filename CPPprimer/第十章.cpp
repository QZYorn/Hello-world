#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
//#include<iterator>
#include<sstream>
#include<vector>
#include<list>
#include<deque>
#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
using namespace std;
using namespace std::placeholders;

void test10_1()
{
	cout << "\n10_1" << endl;

	//10.1
	vector<int> vi{ 0, 1, 1, 2, 3, 5, 8, 13 };
	cout << "count = " << count(vi.begin(), vi.end(), 1) << endl;

	//10.2
	list<string> ls{ "a", "a", "v", "s", "a", "q", "c", "e" };
	cout << "count = " << count(ls.begin(), ls.end(), "a") << endl;
}

void test10_2()
{
	cout << "\n10_2" << endl;

	//10.3
	vector<int> vi{ 0, 1, 1, 2, 3, 5, 8, 13 };
	cout << "accumulate(vi.begin(), vi.end(), 0):" << accumulate(vi.begin(), vi.end(), 0) << endl;

	//10.4
	vector<double> vd{ 0, 1.1, 2, 3.5, 8, 13 };
	accumulate(vd.cbegin(), vd.cend(), 0);

}

void test10_2_2()
{
	cout << "\n10_2_2" << endl;

	//10.6
	vector<int> vi(10, 6);
	auto iter = vi.begin();
	while (iter != vi.end())
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;

	fill_n(vi.begin(), vi.size(), 0);
	iter = vi.begin();
	while (iter != vi.end())
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;

	//10.7
	//a
	vector<int> vec;
	list <int> lst;
	int i;
	while (cin >> i)
	{
		lst.push_back(i);
	}
	copy(lst.cbegin(), lst.cend(), back_inserter(vec));

	//b
	vector<int> vec2;
	vec2.reserve(10);
	vec2.resize(10);
	fill_n(vec2.begin(), 10, 0);
}

template<class VST>
void myPrint(VST &vst)
{
	auto iter = vst.begin();
	while (iter != vst.end())
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;
}

void elimDups(vector<string> &words)
{
	//myPrint(words);
	sort(words.begin(), words.end());
	//myPrint(words);
	words.erase(unique(words.begin(), words.end()),words.end());
	//myPrint(words);
}

void test10_2_3()
{
	//10.9
	vector<string> words{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	elimDups(words);
}

bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

bool big5(const string &s)
{
	return s.size() >= 5;
}

void test10_3_1()
{
	cout << "\n10_3_1" << endl;

	//10.11
	vector<string> words{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	elimDups(words);
	stable_sort(words.begin(), words.end(), isShorter);
	myPrint(words);

	//10.13
	auto end5 = partition(words.begin(), words.end(), big5);
	auto iter = words.begin();
	while (iter != end5)
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;
}

void biggies(vector<string> &words, const int sz)
{
	elimDups(words);

	stable_sort(words.begin(), words.end(), 
	   []( const string &s1, const string &s2)
		 { return s1.size() < s2.size(); });

	////find_if
	//auto iter = find_if(words.begin(), words.end(), 
	//	[sz]( const string &s)
	//		{ return s.size() >= sz; });

	//for_each(iter, words.end(), [](const string &s){ cout << s << " "; });

	//partition
	auto iter = stable_partition(words.begin(), words.end(), 
		[sz]( const string &s)
			{ return s.size() >= sz; });

	for_each(words.begin(), iter, [](const string &s){cout << s << " "; });
	cout << endl;
}

void test10_3_2()
{
	cout << "\n10_3_2" << endl;

	//10.14
	auto sum = [](int a, int b){return a + b; };

	//10.15
	int i = 0;
	auto sum2 = [i](int a){return a + i; };

	//10.16
	vector<string> words{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	biggies(words,5);
}

void test10_3_3()
{
	cout << "\n10_3_3" << endl;

	//10.20
	vector<string> words{ "there", "quickly", "red", "fox", "jumps", "over", "the", "slowky", "red", "turtle" };
	int count = count_if(words.begin(), words.end(), []( const string &s )
													   { return s.size() >= 6; });
	cout << "单词大于等于6的个数：" << count << endl;

	//10.21
	int i = 10;
	auto lam = [&i] () mutable -> bool
				{return i == 0 ? false : i--; };
	while (lam())
	{
		cout << i << " ";
	}
	cout << endl;
}

bool check_size(const string &s, int sz)
{
	return s.size() <= sz;
}

void biggiesBind(vector<string> &words, vector<int>::size_type sz)
{
	elimDups(words);

	stable_sort(words.begin(), words.end(), bind(isShorter,_1,_2));

	
	auto iter = stable_partition(words.begin(), words.end(), bind(check_size,_1,sz));

	for_each(words.begin(), iter, [](const string &s){cout << s << " "; });
	cout << endl;
}

void test10_3_4()
{
	cout << "\n10_3_3" << endl;
	//10.22
	vector<string> words{ "there", "quickly", "red", "fox", "jumps", "over", "the", "slowky", "red", "turtle" };
	int count = count_if(words.begin(), words.end(), bind(check_size, _1, 6));
	cout << "重写bind统计长度小于等于6的单词数量：" << count << endl;

	//10.24
	string s{ "12345" };
	vector<int> ivec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto callable = bind(check_size, s, _1);
	auto iter = find_if(ivec.begin(), ivec.end(), callable);
	cout << "ivec中第一个不小于s长度的值为：" << *iter << endl;

	//10.25
	biggiesBind(words, 3);
}

void test10_4_1()
{
	cout << "\n10_4_1" << endl;

	//10.27
	vector<int> ivec1{ 0, 1, 1, 2, 3, 5, 8, 13 };
	vector<int> ivec2;
	unique_copy(ivec1.begin(), ivec1.end(), back_inserter(ivec2));
	for_each(ivec2.begin(), ivec2.end(), [](int i){cout << i << " "; });

	//10.28
	vector<int> ivec3{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> ivec4{ 0, 0, 0, 0 };
	vector<int> ivec5{ 0, 0, 0, 0 };
	deque<int> dvec6{ 0, 0, 0, 0 };

	copy(ivec3.begin(), ivec3.end(), inserter(ivec4, ++ivec4.begin()));
	copy(ivec3.begin(), ivec3.end(), back_inserter(ivec5));
	copy(ivec3.begin(), ivec3.end(), front_inserter(dvec6));

	cout << "\nivec4:";
	for_each(ivec4.begin(), ivec4.end(), [](int i){cout << i << " "; });
	cout << "\nivec5:";
	for_each(ivec5.begin(), ivec5.end(), [](int i){cout << i << " "; });
	cout << "\ndvec6:";
	for_each(dvec6.begin(), dvec6.end(), [](int i){cout << i << " "; });
}

void fileOddEven(const string &ifile, const string &oofile, const string &eofile)
{
	ifstream ifs(ifile);
	istream_iterator<int> ifs_iter(ifs),eof;
	ofstream oofs(oofile);
	ofstream eofs(eofile);
	ostream_iterator<int> oofs_iter(oofs," "), eofs_iter(eofs,"\n");
	while (ifs_iter != eof)
	{

		if (*ifs_iter % 2 == 1)
		{
			oofs_iter = *ifs_iter;
		}
		else
		{
			eofs_iter = *ifs_iter;
		}
		++ifs_iter;
	}
}

void test10_4_2()
{
	cout << "\n10_4_2" << endl;

	//10.29
	ifstream ifs("test.txt");
	istream_iterator<string> str_in(ifs),seof;
	vector<string> svec;
	copy(str_in, seof, back_inserter(svec));
	ostream_iterator<string> str_out(cout, " ");
	copy(svec.begin(), svec.end(), str_out);
	cout << endl;

	//10.30
	cin.clear();
	istream_iterator<int> int_in(cin), ieof;
	vector<int> ivec(int_in, ieof);
	sort(ivec.begin(), ivec.end());
	ostream_iterator<int> int_out(cout," ");
	cout << "copy:";
	copy(ivec.begin(), ivec.end(), int_out);

	//10.31
	cout << "\nunique_copy:";
	unique_copy(ivec.begin(), ivec.end(), int_out);

	//10.33
	fileOddEven("in.txt", "odd.txt", "even.txt");

}

void test10_4_3()
{
	cout << "\n10_4_2" << endl;

	//10.34
	vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for_each(ivec.rbegin(), ivec.rend(), [](int i){cout << i << " "; });
	cout << endl;

	//10.35
	auto iter = ivec.end() - 1;
	while (iter != ivec.begin())
	{
		cout << *iter-- << " ";
	}
	cout << *iter << endl;

	//10.36
	list<int> ili{ 0, 1, 2, 3, 0, 5, 2, 4, 0, 1, 2, 3, 0 };
	find(ili.rbegin(), ili.rend(), 0);

	//10.37
	vector<double> dvec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	list<double> dli(10);
	copy(dvec.rbegin() + 3, dvec.rbegin() + 8, dli.begin());
	for_each(dli.begin(), dli.end(), [](int i){cout << i << " "; });
}

void test10_5_1()
{
	cout << "\n10_5_1" << endl;

	//10.38
	//输入迭代器 ++iter, =*iter, iter == iter, iter->
	//输出迭代器 ++iter, *iter=
	//前向迭代器 ++iter, *iter=, =*iter, iter == iter, iter->
	//双向迭代器 --iter
	//随机访问迭代器 iter - iter， iter + n， iter < iter ,iter += iter, iter[n] 

	//10.39
	//list上的迭代器为双向迭代器
	//vector上的迭代器属于随机访问迭代器

	//10.40
	//copy要求一对输入迭代器和一个输出迭代器
	//reverse要求一对双向迭代器
	// unique要求一对前向迭代器

	//10.41
	//1.将[beg,end)内所有匹配old_val值的元素替换成new_val
	//2.将[beg,end)内所有满足pred为真的元素替换成new_val
	//3.将[beg,end)内所有匹配old_val值的元素替换成new_val的结果拷贝到dest迭代器指向位置
	//4.将[beg,end)内所有满足pred为真的元素替换成new_val的结果拷贝到dest迭代器指向位置
}

void test10_6()
{
	cout << "\n10_6" << endl;

	//10.42
	list<int> li1{ 1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 5};
	li1.sort();
	li1.unique();

}

int main()
{
	test10_1();
	test10_2();
	test10_2_2();
	test10_2_3();
	test10_3_1();
	test10_3_2();
	test10_3_3();
	test10_3_4();
	test10_4_1();
	test10_4_2();
	test10_4_3();
	test10_5_1();
	test10_6();
	return 0;
}