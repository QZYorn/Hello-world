#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;


template<typename> class BlobPtr;
template<typename T>
class Blob
{
	friend class BlobPtr<T>;
	friend bool operator==(const Blob lb, const Blob rb);
	friend bool operator!=(const Blob lb, const Blob rb);
	friend bool operator<(const Blob lb, const Blob rb);

public:
	typedef vector<T>::size_type size_type;
	Blob() :data(make_shared<vector<T>>()){}
	Blob(initializer_list<T> il) :data(make_shared<vector<T>>(il)){}
	template<typename IT>Blob(IT it1, IT it2) : data(make_shared<vector<T>>(it1, it2)){}
	size_type size() const{ return data->size(); }
	bool empty() const{ return data->empty(); }
	void push_back(const T &s) { data->push_back(s); }
	void pop_back()
	{
		check(0, "pop_back on empty Blob");
		data->pop_back();
	}

	T& front() const
	{
		check(0, "front on empty Blob");
		return data->front();
	}
	T& back() const
	{
		check(0, "back on empty Blob");
		return data->back();
	}

	BlobPtr begin();

	BlobPtr end();

	T& operator[](size_t n){ return (*data)[n]; }
	const T& operator[](size_t n) const { return (*data)[n]; }

private:
	shared_ptr<vector<T>> data;
	void check(size_type i, const T &msg) const
	{
		if (i >= data->size())
			throw out_of_range(msg);
	}
};

template<typename T>
bool operator==(const Blob<T> lb, const Blob<T> rb)
{
	return lb.data == rb.data;
}
template<typename T>
bool operator!=(const Blob<T> lb, const Blob<T> rb)
{
	return !(lb == rb);
	
}
template<typename T>
bool operator<(const Blob<T> lb, const Blob<T> rb)
{
	return *lb.data < *rb.data;
}


template<typename T>
class BlobPtr
{

	friend bool operator==(const BlobPtr& l_sbp, const BlobPtr& r_sbp);
	friend bool operator!=(const BlobPtr& l_sbp, const BlobPtr& r_sbp);
	friend bool operator<(const BlobPtr& l_sbp, const BlobPtr& r_sbp);

public:

	//默认构造
	BlobPtr() :curr(0){}
	//构造
	BlobPtr(Blob<T> &sb, size_t i = 0) :wptr(sb.data), curr(i){}
	//解引用
	T& deref() const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	//前缀递增
	BlobPtr& incr()
	{
		check(curr, "increment past end of BlobPtr");
		++curr;
		return *this;
	}

	//比较操作
	bool eq(const BlobPtr& sb)
	{
		auto l = wptr.lock(), r = sb.wptr.lock();
		if (l == r)
		{
			return (!r || curr == sb.curr);
		}
		return false;
	}

	T& operator[](size_t n){ return (*wptr.lock())[n]; }
	const T& operator[](size_t n)const { return (*wptr.lock())[n]; }
	BlobPtr& operator++(){ return this->incr(); }
	BlobPtr& operator--()
	{
		--curr;
		check(curr, "decrement past begin of BlobPtr");
		return *this;
	}
	BlobPtr operator++(int){ auto ret = *this; ++*this; return ret; }
	BlobPtr operator--(int){ auto ret = *this; --*this; return ret; }
	BlobPtr& operator+(int n){ curr += n; check(curr, "increment past end of BlobPtr"); return *this; }
	BlobPtr& operator-(int n){ curr -= n; check(curr, "decrement past end of BlobPtr"); return *this; }
	T& operator*()const { auto p = check(curr, "dereference past end"); return (*p)[curr]; }
	T* operator->()const { return &this->operator*(); }

private:
	//check，成功就返回vector的shared_ptr
	shared_ptr<vector<T>> check(size_t i, const T &s) const;
	//存一个weak_ptr
	weak_ptr<vector<T>> wptr;
	//curr
	size_t curr;
};
template<typename T>
bool operator==(const BlobPtr<T>& l_sbp, const BlobPtr<T>& r_sbp)
{
	auto left = l_sbp.wptr.lock(), right = r_sbp.wptr.lock();
	if (left == right)
	{
		return (!right || l_sbp.curr == r_sbp.curr);
	}
	return false;
}
template<typename T>
bool operator!=(const BlobPtr<T>& l_sbp, const BlobPtr<T>& r_sbp)
{
	return !(l_sbp == r_sbp);
}
template<typename T>
bool operator<(const BlobPtr<T>& l_sbp, const BlobPtr<T>& r_sbp)
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

template<typename T>
BlobPtr<T> Blob<T>::begin()
{
	return BlobPtr(*this);
}

template<typename T>
BlobPtr<T> Blob<T>::end()
{
	return BlobPtr(*this, data->size());
}

template<typename T>
shared_ptr<vector<T>> BlobPtr<T>::check(size_t i, const T &s) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw runtime_error("unbound StrBlodPtr");
	else if (i > ret->size())
		throw out_of_range(s);
	return ret;

}