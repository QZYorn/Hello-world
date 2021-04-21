#pragma once
#include"listnode.hpp"
#include"List.hpp"

template<class T>
class Queue :public List<T>
{
public:
	void enqueue(T &e)//���
	{
		this->insertAsLast(e);
	}

	T& dequeue()//����
	{
		assert(0 < this->size());
		return this->remove(this->first());
	}

	T& front()//���ö�ͷ
	{
		return this->first();
	}
	T& rear()//���ö�β
	{
		return this->last();
	}
};