#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;



class StrBlobPtr;
class StrBlob
{
	friend class StrBlobPtr;
	friend bool operator==(const StrBlob lb, const StrBlob rb);
	friend bool operator!=(const StrBlob lb, const StrBlob rb);
	friend bool operator<(const StrBlob lb, const StrBlob rb);

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

	string& operator[](size_t n){ return (*data)[n]; }
	const string& operator[](size_t n) const { return (*data)[n]; }

private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const
	{
		if (i >= data->size())
			throw out_of_range(msg);
	}
};

bool operator==(const StrBlob lb, const StrBlob rb)
{
	return lb.data == rb.data;
}
bool operator!=(const StrBlob lb, const StrBlob rb)
{
	return !(lb == rb);
}
bool operator<(const StrBlob lb, const StrBlob rb)
{
	return *lb.data < *rb.data;
}



class StrBlobPtr
{

	friend bool operator==(const StrBlobPtr& l_sbp, const StrBlobPtr& r_sbp);
	friend bool operator!=(const StrBlobPtr& l_sbp, const StrBlobPtr& r_sbp);
	friend bool operator<(const StrBlobPtr& l_sbp, const StrBlobPtr& r_sbp);

public:

	//默认构造
	StrBlobPtr() :curr(0){}
	//构造
	StrBlobPtr(StrBlob &sb, size_t i = 0) :wptr(sb.data), curr(i){}
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

	string& operator[](size_t n){return (*wptr.lock())[n];}
	const string& operator[](size_t n)const { return (*wptr.lock())[n]; }
	StrBlobPtr& operator++(){ return this->incr(); }
	StrBlobPtr& operator--()
	{
		--curr; 
		check(curr, "decrement past begin of StrBlobPtr");
		return *this;
	}
	StrBlobPtr operator++(int){ auto ret = *this; ++*this; return ret; }
	StrBlobPtr operator--(int){ auto ret = *this; --*this; return ret; }
	StrBlobPtr& operator+(int n){ curr += n; check(curr, "increment past end of StrBlobPtr");return *this; }
	StrBlobPtr& operator-(int n){ curr -= n; check(curr, "decrement past end of StrBlobPtr");return *this; }
	string& operator*()const { auto p = check(curr, "dereference past end"); return (*p)[curr]; }
	string* operator->()const { return & this->operator*(); }

private:
	//check，成功就返回vector的shared_ptr
	shared_ptr<vector<string>> check(size_t i, const string &s) const;
	//存一个weak_ptr
	weak_ptr<vector<string>> wptr;
	//curr
	size_t curr;
};

bool operator==(const StrBlobPtr& l_sbp, const StrBlobPtr& r_sbp)
{
	auto left = l_sbp.wptr.lock(), right = r_sbp.wptr.lock();
	if (left == right)
	{
		return (!right || l_sbp.curr == r_sbp.curr);
	}
	return false;
}
bool operator!=(const StrBlobPtr& l_sbp, const StrBlobPtr& r_sbp)
{
	return !(l_sbp == r_sbp);
}
bool operator<(const StrBlobPtr& l_sbp, const StrBlobPtr& r_sbp)
{
	auto left = l_sbp.wptr.lock(), right = r_sbp.wptr.lock();
	if (left == right)
	{
		if (!right)
			return false;
		return l_sbp.curr < r_sbp.curr;
	}
	return false;
}


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
