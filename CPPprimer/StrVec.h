#pragma once

#include<iostream>
#include<string>
#include<algorithm>
using namespace std;


class StrVec
{
	friend bool operator==(const StrVec& l_svec, const StrVec& r_svec);
	friend bool operator!=(const StrVec& l_svec, const StrVec& r_svec);
	friend bool operator< (const StrVec& l_svec, const StrVec& r_svec);


public:
	StrVec() ://Ĭ�Ϲ���
		elements(nullptr), first_free(nullptr), cap(nullptr){}
	StrVec(StrVec&& sv);//�ƶ����캯��
	StrVec(initializer_list<string> ini_list);
	StrVec(const StrVec& sv);//��������
	StrVec& operator=(StrVec&& sv);//�ƶ���ֵ
	StrVec& operator=(const StrVec& sv);//������ֵ
	StrVec& operator=(initializer_list<string> ini_list);
	string& operator[](size_t n){ return *(begin() + n); }
	const string& operator[](size_t n)const{ return *(begin() + n); }

	~StrVec();//����

	void push_back(const string &s);
	template<typename... Args> void emplace_back(const Args&... args);
	size_t  size()	  const{ return first_free - elements; }
	size_t  capacity()const{ return cap - elements; }
	string* begin()   const{ return elements; }
	string* end()	  const{ return first_free; }
	void reserve(const size_t si);
	void resize(const size_t si, string s = "");
private:
	static allocator<string> alloc;

	pair<string*, string*> alloc_n_copy(const string* b, const string* e);//�����ڴ棬������������Χ��Ԫ��
	void chk_n_alloc(){ if (size() == capacity()) reallocate(0); }//���ʣ��ռ䲢������������ڴ�
	void free();	   //���ٹ����Ԫ�ز��ͷ��ڴ�
	void reallocate(size_t si); //�������ڴ�

	string *elements;   //�ڴ��е���Ԫ��
	string *first_free;//���һ��ʵ��Ԫ��֮���λ��
	string *cap;	   //������ڴ�β��λ��
};
allocator<string> StrVec::alloc;

bool operator==(const StrVec& l_svec, const StrVec& r_svec)
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
bool operator!=(const StrVec& l_svec, const StrVec& r_svec)
{
	return !(l_svec == r_svec);
}
bool operator<(const StrVec& l_svec, const StrVec& r_svec)
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



StrVec::StrVec(StrVec&& sv)//�ƶ����캯��
:elements(sv.elements), first_free(sv.first_free), cap(sv.cap)
{
	sv.elements = sv.first_free = sv.cap = nullptr;
}

StrVec::StrVec(initializer_list<string> ini_list)
{
	auto newdata = alloc_n_copy(ini_list.begin(), ini_list.end());
	elements = newdata.first;
	cap = first_free = newdata.second;
}

StrVec::StrVec(const StrVec& sv)
{
	auto newdata = alloc_n_copy(sv.begin(), sv.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec& StrVec::operator=(StrVec&& sv)//�ƶ���ֵ
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

StrVec& StrVec::operator=(const StrVec& sv)
{
	auto data = alloc_n_copy(sv.begin(), sv.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
StrVec& StrVec::operator=(initializer_list<string> ini_list)
{
	auto newdata = alloc_n_copy(ini_list.begin(), ini_list.end());
	elements = newdata.first;
	cap = first_free = newdata.second;
}

StrVec::~StrVec()
{
	free();
}
void StrVec::push_back(const string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

template<typename... Args> 
void StrVec::emplace_back(const Args&... args)
{
	chk_n_alloc();
	alloc.construct(first_free++, forward<Args>(args)...);
}


void StrVec::reserve(const size_t si)
{
	reallocate(si);
}
void StrVec::resize(const size_t si, string s)
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

pair<string*, string*>
StrVec::alloc_n_copy(const string* b, const string* e)
{
	auto data = alloc.allocate(e - b);
	return{ data, uninitialized_copy(b, e, data) };
}

void StrVec::free()
{
	if (elements != nullptr)
	{
		for_each(elements, first_free, [](string& s){alloc.destroy(&s); });
		/*for (auto p = first_free - 1; p != elements; --p)
		{
		alloc.destroy(p);
		}*/
		alloc.deallocate(elements, cap - elements);
	}
}
void StrVec::reallocate(size_t si)
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

void print(StrVec& sv)
{
	for (auto i : sv)
		cout << i << " ";
}