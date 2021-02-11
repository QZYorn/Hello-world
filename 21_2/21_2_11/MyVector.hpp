#pragma once
#include<iostream>
using namespace std;
#include<assert.h>

typedef int Rank;//��
#define DEFAULT_CAPACITY 3//��ʼ����
#define INCREMENT 1//ÿ�ε������ݴ�С
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
	MyVector(int c = DEFAULT_CAPACITY);

	//������������ ���캯��
	MyVector(T const* A, Rank lo, Rank hi);

	//������������ ���캯��
	MyVector(MyVector<T> const& V, Rank lo, Rank hi);

	//������������ ���캯��
	MyVector(MyVector<T> const& V);

	//�������� ���������Ӳ���
	void copyFrom(T const* A, Rank lo, Rank hi);



	//��������
	~MyVector();



	//ֻ���ӿ�
	//����������С
	Rank size();

	//������������
	int capacity();

	//����[]�����
	T operator[](Rank i);



	//ֻд�ӿ�
	//��������
	void expendAdd();

	//�ӱ�����
	void expendDouble();
};



//���캯��
//Ĭ�� ���캯��
template<class T>
MyVector<T>::MyVector(int c = DEFAULT_CAPACITY)
{
	_size = 0;
	_elem = new T[_capacity = c];
}

//������������ ���캯��
template<class T>
MyVector<T>::MyVector(T const* A, Rank lo, Rank hi)
{
	copyFrom(A, lo, hi);
}

//������������ ���캯��
template<class T>
MyVector<T>::MyVector(MyVector<T> const& V, Rank lo, Rank hi)
{
	copyFrom(V._elem, lo, hi);
}

//������������ ���캯��
template<class T>
MyVector<T>::MyVector(MyVector<T> const& V)
{
	copyFrom(V._elem, 0, V._size);
}

//�������� ���������Ӳ���
template<class T>
void MyVector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	_size = 0;
	_elem = new T[_capacity = 2 * (hi - lo)];//Ԥ��һ��������
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}




//��������
template<class T>
MyVector<T>::~MyVector()
{
	assert(_elem);
	delete[] _elem;
	_elem = NULL;
	_size = 0;
	_capacity = 0;
}




//ֻ���ӿ�
//����������С
template<class T>
Rank MyVector<T>::size()
{
	return _size;
}

//������������
template<class T>
int MyVector<T>::capacity()
{
	return _capacity;
}

//����[]�����
template<class T>
T MyVector<T>::operator[](Rank i)
{
	return _elem[i];
}



//ֻд�ӿ�
//��������
template<class T>
void MyVector<T>::expendAdd()
{
	if (_size < _capacity)
		return;
	_capacity = max(_capacity, DEFAULT_CAPACITY);//��������С����

	T *old_elem = _elem;
	_elem = new T[_capacity += INCREMENT];//�¿���
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = old_elem[i];
	}
	delete[] old_elem;//�ͷžɶ����ռ�
}

//�ӱ�����
template<class T>
void MyVector<T>::expendDouble()
{
	if (_size < _capacity)
		return;
	_capacity = max(_capacity, DEFAULT_CAPACITY);//��������С����

	T *old_elem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = old_elem[i];
	}
	delete[] old_elem;
}