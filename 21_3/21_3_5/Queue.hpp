#pragma once
#include"listnode.hpp"
#include"List.hpp"

template<class T>
class Queue :public List<T>
{
public:
	void enqueue(T &e)//入队
	{
		this->insertAsLast(e);
	}

	T& dequeue()//出队
	{
		assert(0 < this->size());
		return this->remove(this->first());
	}

	T& front()//引用队头
	{
		return this->first();
	}
	T& rear()//引用队尾
	{
		return this->last();
	}
};