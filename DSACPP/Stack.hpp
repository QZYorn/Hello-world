#pragma once
#include"ListNode.hpp"
#include"List.hpp"
#include"MyVector.hpp"

template<class T>
class Stack_V :public MyVector<T>
{
public:
	void push(T const &e){ insert(size(), e); }//入栈
	T pop(){ return remove(size() - 1); }//出栈
	T& top(){ return get(size() - 1); }//取顶
};

template<class T>
class LStack :public List<T>
{
public:
	void push(T const &e){ this->insertAsLast(e); }//入栈
	T pop(){ return this->remove(last()); }//出栈
	T& top(){ return last()->data; };//取顶
};