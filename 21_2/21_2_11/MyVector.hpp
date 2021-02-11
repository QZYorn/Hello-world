#pragma once
#include<iostream>
using namespace std;
#include<assert.h>

typedef int Rank;//��
#define DEFAULT_CAPACITY 3//��ʼ����

template<class T>
class MyVector
{
private:
	Rank _size;//������С
	int _capacity;//��������
	T *_elem;//ά������

protected:

public:

	//���캯��
	//Ĭ�� ���캯��
	MyVector(int c = DEFAULT_CAPACITY)
	{
		_size = 0;
		_elem = new T[_capacity = c];
	}

	//������������ ���캯��
	MyVector(T const* A, Rank lo, Rank hi)
	{
		copyFrom(A, lo, hi);
	}

	//������������ ���캯��
	MyVector(MyVector<T> const& V, Rank lo, Rank hi)
	{
		copyFrom(V._elem, lo, hi);
	}

	//������������ ���캯��
	MyVector(MyVector<T> const& V)
	{
		copyFrom(V._elem, 0, V._size);
	}

	//�������� ���������Ӳ���
	void copyFrom(T const* A, Rank lo, Rank hi)
	{
		_size = 0;
		_elem = new T[_capacity = 2 * (hi - lo)];
		while (lo < hi)
		{
			_elem[_size++] = A[lo++];
		}
	}

	

	//��������
	~MyVector()
	{
		assert(_elem);
		delete[] _elem;
		_elem = NULL;
		_size = 0;
		_capacity = 0;
	}



	//ֻ���ӿ�
	//����������С
	Rank size()
	{
		return _size;
	}

	//������������
	int capacity()
	{
		return _capacity;
	}

	//����[]�����
	T operator[](Rank i)
	{
		return _elem[i];
	}
};