#pragma once
#include"ListNode.hpp"
#include"List.hpp"
#include"MyVector.hpp"

template<class T>
class Stack_V :public MyVector<T>
{
public:
	void push(T const &e){ insert(size(), e); }//��ջ
	T pop(){ return remove(size() - 1); }//��ջ
	T& top(){ return get(size() - 1); }//ȡ��
};

template<class T>
class LStack :public List<T>
{
public:
	void push(T const &e){ this->insertAsLast(e); }//��ջ
	T pop(){ return this->remove(last()); }//��ջ
	T& top(){ return last()->data; };//ȡ��
};