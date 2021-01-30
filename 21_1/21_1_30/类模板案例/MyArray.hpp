#pragma once
#include<iostream>
#include<string>
using namespace std;
#include<assert.h>

template<class T>
class MyArray
{
public:
	MyArray(int capacity)//���캯��
	{
		//cout << "���캯��" << endl;
		m_Arr = new T[capacity];
		m_Capacity = capacity;
		m_Size = 0;
	}

	MyArray(MyArray &arr)//�������캯��
	{
		//cout << "�������캯��" << endl;
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->m_Arr = new T[arr.m_Capacity];
		for (int i = 0; i < arr.m_Size; i++)
		{
			this->m_Arr[i] = arr.m_Arr[i];
		}
	}

	MyArray& operator=(MyArray &arr)//��ֵ��������غ���
	{
		//cout << "��ֵ��������غ���" << endl;
		delete[] this->m_Arr;
		this->m_Arr = new T[arr.m_Capacity];
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		for (int i = 0; i < arr.m_Size; i++)
		{
			this->m_Arr[i] = arr.m_Arr[i];
		}
		return *this;
	}

	 T& operator[](int index)//�Ǳ����
	{
		return m_Arr[index];
	}

	void Add(const T& val)//β�巨
	{
		if (m_Size == m_Capacity)
		{
			cout << "�����������޷�����" << endl;
			return;

		}
		m_Arr[m_Size] = val;
		m_Size++;
	}

	void Del()//βɾ��
	{
		if (m_Size == 0)
		{
			cout << "�����ѿգ��޷�ɾ��" << endl;
			return;

		}
		m_Size--;
	}

	int getCapacity()//��ȡ����
	{
		return m_Capacity;
	}

	int getSize()//��ȡ��С
	{
		return m_Size;
	}

	~MyArray()//��������
	{
		//cout << "��������" << endl;
		assert(m_Arr != NULL);
		delete[] this->m_Arr;
		this->m_Arr = NULL;
	}

private:
	T *m_Arr;//ָ��������Ԫ�أ�ά������
	int m_Capacity;//�������
	int m_Size;//��ǰ��С
};