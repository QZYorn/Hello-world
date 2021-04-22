#pragma once
#include<iostream>
using namespace std;
#include<assert.h>
#include"Fib.h"

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

	//�������� ���ֲ��� A
	Rank binSearchA(T const* A, T const& e, Rank lo, Rank hi);

	//�������� ���ֲ��� B
	Rank binSearchB(T const* A, T const& e, Rank lo, Rank hi);

	//�������� ���ֲ��� C
	Rank binSearchC(T const* A, T const& e, Rank lo, Rank hi);

	//�������� 쳲���������
	Rank fibSearch(T const* A, T const& e, Rank lo, Rank hi);

	//������������ ��ֵ����
	Rank intSearch(T const* A, T const& e, Rank lo, Rank hi);

	//���� ð�ݽӿ� һ�θĽ�
	bool bubbleA(Rank lo, Rank hi);

	//���� ð�ݽӿ� ���θĽ�
	Rank bubbleB(Rank lo, Rank hi);

	//ð������
	void bubbleSort(Rank lo, Rank hi);

	//�鲢���� ���㷨
	void mergeSort(Rank lo, Rank hi);

	//�鲢���� �ϲ�����
	void merge(Rank lo,Rank mi, Rank hi);


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
	Rank size() const;

	//�ж��Ƿ�Ϊ��
	bool empty() const{ return !_size; }

	//������������
	int capacity();

	//�ж������Ƿ��Ѿ����򣬷�������Ը���
	int disordered();

	//�������� ���� ����ָ��Ԫ��,�ɹ�����Ԫ���ȣ�ʧ�ܷ�������ǰ��
	Rank find(T const& e, Rank lo, Rank hi);

	//�������� ���� ����ָ��Ԫ��,�ɹ�����Ԫ���ȣ�ʧ�ܷ�������ǰ��
	Rank find(T const& e);

	//�������� ���� ����ָ��Ԫ��,�ɹ�����Ԫ���ȣ�ʧ�ܷ�����������
	Rank search(T const& e, Rank lo, Rank hi);

	//�������� ���� ����ָ��Ԫ��,�ɹ�����Ԫ���ȣ�ʧ�ܷ�����������
	Rank search(T const& e);



	//ֻд�ӿ�
	//�� ��i Ԫ�� ���� ָ��Ԫ��
	void put(Rank r, T const& e);

	//����r������Ԫ��e,������
	Rank insert(Rank r, T const& e);

	//����ɾ��,����ɾ��Ԫ�ظ���
	int remove(Rank lo, Rank hi);

	//��Ԫ��ɾ��,���ر�ɾ����Ԫ��
	T remove(Rank r);

	//�������� ȥ�ز���,���ر�ɾ��Ԫ�ظ���
	int deduplicate();

	//�������� ��Ч ȥ�ز���,���ر�ɾ��Ԫ�ظ���
	int uniquifyLow();

	//�������� ��Ч ȥ�ز���,���ر�ɾ��Ԫ�ظ���
	int uniquifyHigh();

	//��������
	void sort(Rank lo, Rank hi);

	//��������
	void sort();



	//����
	//����ָ��/�ص�����
	void traverse(void(*visit)(T&));

	//��������/α����
	template<class VST>
	void traverse(VST& visit);
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

//�������� ���ֲ��� A
template<class T>
Rank MyVector<T>::binSearchA(T const* A,T const& e, Rank lo, Rank hi)
{
	while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1;//���е�Ϊ�ᣬ[lo,mi) [mi] (mi,hi)
		if (e < A[mi])//�������
		{
			hi = mi;
		}
		else if (A[mi] < e)//�����Ұ�
		{
			lo = mi + 1;
		}
		else
		{
			return mi;//�ɹ����з�����
		}
	}
	return -1;//ʧ�ܷ���-1
}

//�������� ���ֲ��� B
template<class T>
Rank MyVector<T>::binSearchB(T const* A, T const& e, Rank lo, Rank hi)
{
	while (1 < hi - lo )
	{
		Rank mi = (hi + lo) >> 1;
		(e < _elem[mi]) ? (hi = mi) : (lo = mi);//[lo,mi) [mi,hi)
	}//����ʱhi = lo +1,�����ʣһ��_elem[lo]
	return (_elem[lo] == e) ? lo : -1;
}

//�������� ���ֲ��� C
template<class T>
Rank MyVector<T>::binSearchC(T const* A, T const& e, Rank lo, Rank hi)
{
	while (lo < hi)
	{
		Rank mi = (hi + lo) >> 1;
		(e < _elem[mi]) ? (hi = mi) : (lo = mi+1);//[lo,mi) (mi,hi)
	}//����ʱhi == lo,_elem[lo-1]Ϊ������e�����ֵ��_elem[hi]Ϊ����e����Сֵ
	return --lo;
}




//�������� 쳲���������
template<class T>
Rank MyVector<T>::fibSearch(T const* A, T const& e, Rank lo, Rank hi)
{
	Fib fib(hi - lo);

	while (lo < hi)
	{
		while (hi - lo < fib.get())
		{
			fib.prev();
		}
		Rank mi = lo + fib.get()-1;//��Fib(k-1)Ϊ��,
		if (e < A[mi])//�������
		{
			hi = mi;
		}
		else if (A[mi] < e)//�����Ұ�
		{
			lo = mi + 1;
		}
		else
		{
			return mi;//�ɹ����з�����
		}
	}
	return -1;
}

//������������ ��ֵ����
template<class T>
Rank MyVector<T>::intSearch(T const* A, T const& e, Rank lo, Rank hi)
{
	--hi;
	while (lo < hi)
	{
		Rank mi = lo + (hi - lo)*(e - _elem[lo]) / (_elem[hi] - _elem[lo]);
		(e < _elem[mi]) ? hi = mi : lo = mi+1;
	}
	return --lo;
}

//���� ð�ݽӿ�
template<class T>
bool MyVector<T>::bubbleA(Rank lo, Rank hi)
{
	bool sorted = true;//������Ա�־
	while (++lo < hi)//����������ڶ�
	{
		if (_elem[lo - 1] > _elem[lo])//���������ʱ
		{
			sorted = false;//��־��Ϊfalse
			swap(_elem[lo - 1], _elem[lo]);//���������
		}
	}
	return sorted;//�����Ƿ��������
}

//���� ð�ݽӿ� ���θĽ�
template<class T>
Rank MyVector<T>::bubbleB(Rank lo, Rank hi)
{
	Rank last = lo;//��ʼ�����������
	while (++lo < hi)
	{
		if (_elem[lo - 1]  > _elem[lo])
		{
			last = lo;//�������������λ��
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return last;
}

//ð������
template<class T>
void MyVector<T>::bubbleSort(Rank lo, Rank hi)
{
	switch (rand()%2)
	{
	case 1:
		while (!bubbleA(lo, hi--));
		break;
	default:
		while (lo < (hi = bubbleB(lo, hi)));//�����������λ�ÿ�ʼ��һ������ɨ�裬�����������ʱ�˳�ѭ��
		break;
	}
	
}

//�鲢���� ���㷨
template<class T>
void MyVector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2)//�ݹ��
	{
		return;
	}
	Rank mi = (lo + hi) >> 1;//�е�Ϊ�ᣬ[lo,mi) [mi,hi)
	mergeSort(lo, mi);//��ǰ�������  B
	mergeSort(mi, hi);//�Ժ�������  C
	merge(lo, mi, hi);//B �� C �鲢Ϊ A
}

//�鲢���� �ϲ�����
template<class T>
void MyVector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* A = _elem + lo;//A����ʼλ��Ϊ_elem����ַ + ��ʼƫ����

	int lb = mi - lo;//B������
	T* B = new T[lb];//��B�����л��壬��ֹ����
	for (Rank i = 0; i < lb; B[i] = A[i++]);//����ԭ����

	int lc = hi - mi; //C������
	T* C = _elem + mi;//C����ʼλ��Ϊ_elem����ַ + ����ƫ����
	//����C��������A���ϣ�C��ʣ��ʱ�����в�������ԭ��
	for (Rank i = 0, j = 0, k = 0; j < lb;)
	{
		if ((lc <= k) || (B[j] <= C[k]))
		{
			A[i++] = B[j++];
		}
		if ((k <  lc) && (C[k] <  B[j]))
		{
			A[i++] = C[k++];
		}
	}
	//C��ʣ��ʱ���ಽ������Ų��A��
	/*for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
	{
		if ((j < lb) && ((lc <= k) || (B[j] <= C[k])))
		{
			A[i++] = B[j++];
		}
		if ((k < lc) && ((lb <= j) || (C[k] < B[j])))
		{
			A[i++] = C[k++];
		}
	}*/
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
Rank MyVector<T>::size() const
{
	return _size;
}

//������������
template<class T>
int MyVector<T>::capacity()
{
	return _capacity;
}

//�ж������Ƿ��Ѿ����򣬷�������Ը���
template<class T>
int MyVector<T>::disordered()
{
	int count = 0;
	for (int i = 1; i < _size; i++)
	{
		if (_elem[i - 1] >_elem[i])
		{
			count++;
		}
	}
	return count;
}


//�������� ���� ����ָ��Ԫ�أ��ɹ�����Ԫ���ȣ�ʧ�ܷ�����������
template<class T>
Rank MyVector<T>::find(T const& e, Rank lo, Rank hi)
{
	assert(0 <= lo&&lo <= hi&&hi <= _size);

	while (lo < hi-- && _elem[hi] != e);
	return hi;
}

//�������� ���� ����ָ��Ԫ��,�ɹ�����Ԫ���ȣ�ʧ�ܷ�����������
template<class T>
Rank MyVector<T>::find(T const& e)
{
	return find(e, 0, _size);
}

//�������� ���� ����ָ��Ԫ��,�ɹ�����Ԫ���ȣ�ʧ�ܷ�����������
template<class T>
Rank MyVector<T>::search(T const& e, Rank lo, Rank hi)
{
	assert(0 <= lo&&lo <= hi&&hi <= _size);

	return (rand() % 2)
		? binSearchA(_elem, e, lo, hi)
		: fibSearch(_elem, e, lo, hi);
}

//�������� ���� ����ָ��Ԫ��,�ɹ�����Ԫ���ȣ�ʧ�ܷ�����������
template<class T>
Rank MyVector<T>::search(T const& e)
{
	return search(e, 0, _size);
}




//ֻд�ӿ�
//�� �� Ԫ�� ���� ָ��Ԫ��
template<class T>
void MyVector<T>::put(Rank r, T const& e)
{
	assert(r >= 0 && r <= _size);
	_elem[r] = e;
}

//����r������Ԫ��e,������
template<class T>
Rank MyVector<T>::insert(Rank r, T const& e)
{
	assert(r >= 0 && r <= _size);

	expandDouble();
	
	for (int i = _size; i > r; i--)//��׺��Ųһλ
	{
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e;//����Ԫ��
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

//ȥ�ز���,���ر�ɾ��Ԫ�ظ���
template<class T>
int MyVector<T>::deduplicate()
{
	int old_size = _size;//��¼ԭ��ģ
	Rank i = 1;//��_elem[1]��ʼ
	while (i < _size)
	{
		find(_elem[i], 0, i) > 0 ? remove(i) : i++;//��ǰ׺�� ���ҳɹ� ��ɾ����ǰԪ�أ�ʧ���������һλ
	}
	return old_size - _size ;//�����¾ɹ�ģ��
}

//��������  ��Ч ȥ�ز���,���ر�ɾ��Ԫ�ظ���
template<class T>
int MyVector<T>::uniquifyLow()
{
	int old_size = _size;
	int i = 1;
	while (i < _size)
	{
		(_elem[i] == _elem[i - 1]) ? remove(i) : i++;
	}
	return old_size - _size;
}

//��������  ��Ч ȥ�ز���,���ر�ɾ��Ԫ�ظ���
template<class T>
int MyVector<T>::uniquifyHigh()
{
	int i = 0;
	int j = 0;
	while ( ++j < _size)
	{
		if (_elem[i] != _elem[j])
		{
			_elem[++i] = _elem[j];
		}
	}
	_size = ++i;
	shrink();
	return j - i;
}

//��������
template<class T>
void MyVector<T>::sort(Rank lo, Rank hi)
{
	switch (rand()%2)
	{
	case 0:
		bubbleSort(lo, hi);
		break;
	case 1:
		mergeSort(lo, hi);
		break;
	//case 2:
	//	break;
	//case 3:
	//	break;
	//case 4:
	//	break;
	}
}

//��������
template<class T>
void MyVector<T>::sort()
{
	sort(0, _size);
}






//����
//����ָ��/�ص�����
template<class T>
void MyVector<T>::traverse(void(*visit)(T&))
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}

//��������/α����
template<class T>
template<class VST>
void MyVector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}