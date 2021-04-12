#pragma once

#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

template<typename T>
class Vec
{
	friend bool operator==(const Vec& l_svec, const Vec& r_svec);
	friend bool operator!=(const Vec& l_svec, const Vec& r_svec);
	friend bool operator< (const Vec& l_svec, const Vec& r_svec);


public:
	Vec() ://默认构造
		elements(nullptr), first_free(nullptr), cap(nullptr){}
	Vec(Vec&& sv);//移动构造函数
	Vec(initializer_list<T> ini_list);
	Vec(const Vec& sv);//拷贝构造
	Vec& operator=(Vec&& sv);//移动赋值
	Vec& operator=(const Vec& sv);//拷贝赋值
	Vec& operator=(initializer_list<T> ini_list);
	T& operator[](size_t n){ return *(begin() + n); }
	const T& operator[](size_t n)const{ return *(begin() + n); }

	~Vec();//析构

	void push_back(const T &s);
	size_t  size()	  const{ return first_free - elements; }
	size_t  capacity()const{ return cap - elements; }
	T* begin()   const{ return elements; }
	T* end()	  const{ return first_free; }
	void reserve(const size_t si);
	void resize(const size_t si, T s = "");
private:
	static allocator<T> alloc;

	pair<T*, T*> alloc_n_copy(const T* b, const T* e);//分配内存，并拷贝给定范围内元素
	void chk_n_alloc(){ if (size() == capacity()) reallocate(0); }//检查剩余空间并根据情况分配内存
	void free();	   //销毁构造的元素并释放内存
	void reallocate(size_t si); //分配新内存

	T *elements;   //内存中的首元素
	T *first_free;//最后一个实际元素之后的位置
	T *cap;	   //分配的内存尾后位置
};
template<typename T>
allocator<T> Vec::alloc;

template<typename T>
bool operator==(const Vec& l_svec, const Vec& r_svec)
{
	if (l_svec.size() != r_svec.size())
		return false;
	for (auto lit = l_svec.begin(), rit = r_svec.begin(); lit != l_svec.end() && rit != r_svec.end(); ++lit, ++rit)
	{
		if (*lit != *rit)
			return false;
	}
	return true;
}
template<typename T>
bool operator!=(const Vec& l_svec, const Vec& r_svec)
{
	return !(l_svec == r_svec);
}
template<typename T>
bool operator<(const Vec& l_svec, const Vec& r_svec)
{
	if (l_svec.size() != r_svec.size())
		return l_svec.size() < r_svec.size();
	for (auto lit = l_svec.begin(), rit = r_svec.begin(); lit != l_svec.end() && rit != r_svec.end(); ++lit, ++rit)
	{
		if (*lit != *rit)
			return *lit < *rit;
	}
	return false;
}


template<typename T>
Vec<T>::Vec(Vec&& sv)//移动构造函数
:elements(sv.elements), first_free(sv.first_free), cap(sv.cap)
{
	sv.elements = sv.first_free = sv.cap = nullptr;
}

template<typename T>
Vec<T>::Vec(initializer_list<T> ini_list)
{
	auto newdata = alloc_n_copy(ini_list.begin(), ini_list.end());
	elements = newdata.first;
	cap = first_free = newdata.second;
}

template<typename T>
Vec<T>::Vec(const Vec& sv)
{
	auto newdata = alloc_n_copy(sv.begin(), sv.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

template<typename T>
Vec<T>& Vec<T>::operator=(Vec&& sv)//移动赋值
{
	if (&sv != this)
	{
		free();
		elements = sv.elements;
		first_free = sv.first_free;
		cap = sv.cap;
		sv.elements = sv.first_free = sv.cap = nullptr;
	}
	return *this;
}

template<typename T>
Vec<T>& Vec::operator=(const Vec& sv)
{
	auto data = alloc_n_copy(sv.begin(), sv.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
template<typename T>
Vec<T>& Vec<T>::operator=(initializer_list<T> ini_list)
{
	auto newdata = alloc_n_copy(ini_list.begin(), ini_list.end());
	elements = newdata.first;
	cap = first_free = newdata.second;
}

template<typename T>
Vec<T>::~Vec()
{
	free();
}
template<typename T>
void Vec<T>::push_back(const T &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

template<typename T>
void Vec<T>::reserve(const size_t si)
{
	reallocate(si);
}
template<typename T>
void Vec<T>::resize(const size_t si, T s)
{
	if (size() < si)
	{
		if (capacity() < si)
		{
			reallocate(si);
		}
		for (size_t b = size(); b < si; ++b)
			alloc.construct(first_free++, s);
	}
	else if (si < size())
	{
		for (size_t b = size(); si < b; --b)
			alloc.destroy(--first_free);
	}
}

template<typename T>
pair<T*, T*>
Vec<T>::alloc_n_copy(const T* b, const T* e)
{
	auto data = alloc.allocate(e - b);
	return{ data, uninitialized_copy(b, e, data) };
}

template<typename T>
void Vec<T>::free()
{
	if (elements != nullptr)
	{
		for_each(elements, first_free, [](T& s){alloc.destroy(&s); });
		/*for (auto p = first_free - 1; p != elements; --p)
		{
		alloc.destroy(p);
		}*/
		alloc.deallocate(elements, cap - elements);
	}
}
template<typename T>
void Vec<T>::reallocate(size_t si)
{
	auto newcapacity = si;
	if (si <= size())
		newcapacity = size() ? size() * 2 : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
	{
		alloc.construct(dest++, move(*elem++));
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = newdata + newcapacity;
}

template<typename T>
void print(Vec<T>& sv)
{
	for (auto i : sv)
		cout << i << " ";
}