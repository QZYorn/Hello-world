#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
//#include<iterator>
#include<sstream>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
#include<memory>
using namespace std;
using namespace std::placeholders;

class StrBlobPtr;
class StrBlob
{
	friend class StrBlobPtr;
public:
	typedef vector<string>::size_type size_type;
	StrBlob() :data(make_shared<vector<string>>()){}
	StrBlob(initializer_list<string> il) :data(make_shared<vector<string>>(il)){}
	size_type size() const{ return data->size(); }
	bool empty() const{ return data->empty(); }

	void push_back(const string &s) { data->push_back(s); }
	void pop_back()
	{
		check(0, "pop_back on empty StrBlob");
		data->pop_back();
	}

	string& front() const
	{
		check(0, "front on empty StrBlob");
		return data->front();
	}
	string& back() const
	{
		check(0, "back on empty StrBlob");
		return data->back();
	}

	StrBlobPtr begin();

	StrBlobPtr end();
private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const
	{
		if (i >= data->size())
			throw out_of_range(msg);
	}
};

class StrBlobPtr
{
public:

	//默认构造
	StrBlobPtr():curr(0){}
	//构造
	StrBlobPtr(StrBlob &sb, size_t i =0):wptr(sb.data), curr(i){}
	//解引用
	string& deref() const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	//前缀递增
	StrBlobPtr& incr()
	{
		check(curr, "increment past end of StrBlobPtr");
		++curr;
		return *this;
	}

	//比较操作
	bool eq(const StrBlobPtr& sb)
	{
		auto l = wptr.lock(), r = sb.wptr.lock();
		if (l == r)
		{
			return (!r || curr == sb.curr);
		}
		return false;
	}
private:
	//check，成功就返回vector的shared_ptr
	shared_ptr<vector<string>> check (size_t i, const string &s) const;
	//存一个weak_ptr
	weak_ptr<vector<string>> wptr;
	//curr
	size_t curr;
};

StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this, data->size());
}


shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &s) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw runtime_error("unbound StrBlodPtr");
	else if (i > ret->size())
		throw out_of_range(s);
	return ret;

}

vector<int>* vei()
{
	return new vector<int>();
}

void print(vector<int>* vei_ptr)
{
	for (auto i : *vei_ptr)
		cout << i << " ";
}

void read(vector<int>* vei_ptr)
{
	int i;
	while (cin >> i)
	{
		vei_ptr->push_back(i);
	}
}

shared_ptr<vector<int>> vei_shared()
{
	return make_shared<vector<int>>();
}

void print_shared(shared_ptr<vector<int>> vei_ptr)
{
	for (auto i : *vei_ptr)
		cout << i << " ";
}

void read_shared(shared_ptr<vector<int>> vei_ptr)
{
	int i;
	while (cin >> i)
	{
		vei_ptr->push_back(i);
	}
}

void test12_1_2()
{
	cout << "\n12.1.2" << endl;

	//12.6
	auto vei_ptr = vei();
	if (!vei_ptr)
	{
		cout << "内存不足" << endl;
			return;
	}
	read(vei_ptr);
	print(vei_ptr);
	delete vei_ptr;
	vei_ptr = nullptr;

	//12.7
	auto vei_shared_ptr = vei_shared();
	if (!vei_shared_ptr)
	{
		cout << "内存不足" << endl;
		return;
	}
	read_shared(vei_shared_ptr);
	print_shared(vei_shared_ptr);
}

struct connection{};
struct destination{};
connection connect(destination* d)
{
	//cout << *d << endl;
	cout << "打开连接" << endl;
	return connection();
}
void disconnection(connection& c)
{
	//delete c;
	cout << "关闭连接" << endl;

}
void f(destination &d)
{
	connection c = connect(&d);
	//
	//
	//意外结束
	//cout << endl;
	disconnection(c);
}
void end_connection(connection* c){ disconnection(*c); }

void f2(destination &d)
{
	connection c = connect(&d);
	//12.14
	//shared_ptr<connection> p(&c, end_connection);
	//12.15
	shared_ptr<connection> p(&c, [](connection*pc){disconnection(*pc); });
}

void test12_1_5()
{
	cout << "\n12.1.5" << endl;

	int i = 0;
	unique_ptr<int> u1;
	unique_ptr<int> u2(new int(i));
	//unique_ptr<int> u3(u2);//拷贝构造
	//unique_ptr<int> u4 = u1;
	//u2 = u1;//赋值操作
}

void test12_1_6()
{
	cout << "\n12.1.6" << endl;

	ifstream ifs("test.txt");
	if (!ifs.is_open())
	{
		cout << "file can not open " << endl;
		return;
	}
	StrBlob sb;
	string s;
	while (ifs >> s)
	{
		sb.push_back(s);
	}
	
	for (auto it = sb.begin(); !it.eq(sb.end());it.incr())
	{
		cout << it.deref() << endl;
	}
	ifs.close();
}

void test12_2_1()
{
	cout << "\n12.2.1" << endl;

	//12.23
	char* chr_ptr = new char[10];
	strcpy(chr_ptr, "aaa");
	strcat(chr_ptr + strlen("aaa"), "ccc");
	/*for (auto it = chr_ptr; it != chr_ptr + 10; ++it)
	{
		cout << *it;
	}*/
	cout << chr_ptr << endl;
	delete[] chr_ptr;
	chr_ptr = nullptr;

	string s1{ "aaa2" };
	string s2{ "ccc2" };
	char* chr_ptr2 = new char[s1.size()+s2.size()];
	strcpy(chr_ptr2, (s1+s2).c_str());
	/*for (auto it = chr_ptr2; it != chr_ptr2 + s1.size() + s2.size(); ++it)
	{
		cout << *it;
	}*/
	cout << chr_ptr2 << endl;

	//12.24
	unique_ptr<char[]> up(new char[5]());
	//unique_ptr<char[]> nup;
	string s;
	while (cin >> s)
	{
		int old_size = sizeof(up.get());
		if (s.size() > old_size)
		{
			int new_size = s.size()*1.5;
			unique_ptr<char[]> nup(new char[new_size]);
			swap(nup,up);
		}
		strcpy(up.get(), s.c_str());
	}
	cout << up.get() << endl;

	//12.25
	int *pa = new int[10];
	delete[] pa;

}

void test12_2_2()
{
	cout << "\n12.2.2" << endl;

	//12.26
	allocator<string> al;
	auto const p = al.allocate(10);//首元素
	auto q = p;//尾元素
	string s;
	while (cin >> s && q != p + 10)
	{
		al.construct(q++, s);
	}
	const size_t size = q - p;
	while (q != p)
	{
		al.destroy(--q);
	}
	al.deallocate(p,10);
}


class QueryResult;
class TextQuery
{
public:
	typedef size_t line_no;
	TextQuery(ifstream &ifs) :file(new vector<string>)
	{
		string s;
		int curr = 0;
		while (getline(ifs,s))
		{
			file->push_back(s);
			string word;
			istringstream iss(s);
			while (iss >> word)
			{
				auto &line = word_line[word];
				if (!line)
				{
					line.reset(make_shared<set<line_no>>);
				}
				line->insert(curr);
			}
			++curr;
		}
	}

	QueryResult query(const string& s) const;

private:

	shared_ptr<vector<string>> file;
	map<string, shared_ptr<set<line_no>>> word_line;
};

class QueryResult
{
	friend ostream& print(ostream& os, QueryResult& qr);

	typedef size_t line_no;
public:
	QueryResult(string s,
		shared_ptr<vector<string>> p,
		shared_ptr<set<line_no>> l)
		:word(s), file(p), line(l){}
private:
	string word;
	shared_ptr<vector<string>> file;
	shared_ptr<set<line_no>> line;

};

QueryResult TextQuery::query(const string& s) const
{
	auto line = word_line.find(s);
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	if (line == word_line.end())
	{
		return{ s, file, nodata};
	}
	return{ s, file, line->second };
}

ostream& print(ostream& os, QueryResult& qr)
{
	os << qr.word << " occurs "
		<< qr.line->size() << (1 < qr.line->size() ? " times " : " time ")
		<< endl;
	for (auto c : *qr.line)
	{
		os << "\t(line" << c+1  << ")"
			<< (*qr.file)[c] << endl;
	}
	return os;
}

void runQuries(ifstream &infile)
{
	TextQuery tq(infile);
	while (true)
	{
		cout << "输入要查找的单词，或输入q退出: ";
		string s;
		if (!(cin >> s) || s == "q")
			break;
		print(cout, tq.query(s)) << endl;
	}
}

void test12_3_1()
{
	cout << "\n12.3.1" << endl;

	//12.27
	
}

int main()
{
	//test12_1_2();
	//test12_1_5();
	//test12_1_6();
	//test12_2_1();
	//test12_2_2();
	test12_3_1();
	return 0;
}