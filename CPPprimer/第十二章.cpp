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

class StrBlob
{
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
private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const
	{
		if (i >= data->size())
			throw out_of_range(msg);
	}
};

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

int main()
{
	test12_1_2();
	return 0;
}