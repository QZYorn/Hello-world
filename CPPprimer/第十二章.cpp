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

int main()
{
	//test12_1_2();
	//test12_1_5();
	test12_1_6();
	return 0;
}