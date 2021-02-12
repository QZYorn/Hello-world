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
	//�ڲ�����
	//��������
	void expandAdd();

	//�ӱ�����
	void expandDouble();

	//����
	void shrink();


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
	//��ȡ �� Ԫ��
	T& get(Rank i);

	//����[]�����
	T& operator[](Rank r);

	//����������С
	Rank size();

	//������������
	int capacity();

	



	//ֻд�ӿ�
	//�� ��i Ԫ�� ���� ָ��Ԫ��
	void put(Rank r, T t);

	//����r������Ԫ��t,������
	Rank insert(Rank r, T const& t);

	//����ɾ��,����ɾ��Ԫ�ظ���
	int remove(Rank lo, Rank hi);

	//��Ԫ��ɾ��,���ر�ɾ����Ԫ��
	T remove(Rank r);
};



//�ڲ�����
//��������
template<class T>
void MyVector<T>::expandAdd()
{
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)//��������С����
		_capacity = DEFAULT_CAPACITY;

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
void MyVector<T>::expandDouble()
{
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)//��������С����
		_capacity = DEFAULT_CAPACITY;

	T *old_elem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = old_elem[i];
	}
	delete[] old_elem;
}

//����
template<class T>
void MyVector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1)//������������DEFAULT_CAPACITY����
		return;
	if (_size > _capacity >> 2)//25%װ������Ϊ��
		return;
	T *old_elem = _elem;
	_elem =	new T[_capacity >>= 1];//��������, ��������
	for (int i = 0; i < _size; i++)//����ԭ����Ԫ��
	{
		_elem[i] = old_elem[i];
	}
	delete[] old_elem;//�ͷž�����
	old_elem = NULL;
}

//���캯��
//Ĭ�� ���캯��
template<class T>
MyVector<T>::MyVector(int c = DEFAULT_CAPACITY)
{
	_size = 0;
	_elem = new T[_capacity = max(c, DEFAULT_CAPACITY)];
}

//������������ ���캯��
template<class T>
MyVector<T>::MyVector(T const* A, Rank lo, Rank hi)
{
	assert(A != NULL);
	copyFrom(A, lo, hi);
}

//������������ ���캯��
template<class T>
MyVector<T>::MyVector(MyVector<T> const& V, Rank lo, Rank hi)
{
	assert(V._elem != NULL);
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
	assert(_elem != NULL);
	delete[] _elem;
	_elem = NULL;
	_size = 0;
	_capacity = 0;
}




//ֻ���ӿ�
//��ȡ �� Ԫ��
template<class T>
T& MyVector<T>::get(Rank i)
{
	assert(i >= 0 && i <= _size);
	return _elem[i];
}

//����[]�����
template<class T>
T& MyVector<T>::operator[](Rank r)
{
	assert(r >= 0 && r <= _size);
	return _elem[r];
}

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




//ֻд�ӿ�
//�� �� Ԫ�� ���� ָ��Ԫ��
template<class T>
void MyVector<T>::put(Rank r, T t)
{
	assert(r >= 0 && r <= _size);
	_elem[r] = t;
}

//����r������Ԫ��t,������
template<class T>
Rank MyVector<T>::insert(Rank r, T const& t)
{
	assert(r >= 0 && r <= _size);

	expandDouble();
	
	for (int i = _size; i > r; i--)//��׺��Ųһλ
	{
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = t;//����Ԫ��
	_size++;//���´�С
	return r;
}

//����ɾ��,����ɾ��Ԫ�ظ���
template<class T>
int MyVector<T>::remove(Rank lo, Rank hi)
{
	assert(0 <= lo&&lo <= hi&&hi <= _size);

	if (lo == hi)
		return 0;

	while (hi < _size)
	{
		_elem[lo++] = _elem[hi++];
	}
	_size = lo;//���´�С
	shrink();//��װ�����ӹ��ͣ�����
	return hi - lo;
}

//��Ԫ��ɾ��,���ر�ɾ����Ԫ��
template<class T>
T MyVector<T>::remove(Rank r)
{
	assert(r >= 0 && r <= _size);

	T tmp = _elem[r];//���ݱ�ɾ��Ԫ��
	remove(r, r + 1);
	return tmp;//���ر�ɾ��Ԫ��
}