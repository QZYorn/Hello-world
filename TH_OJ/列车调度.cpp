#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
using namespace std;
#define MAX 1600004//1600,000
class Stack
{
private:
	int _size;
	int *_elem;
public:
	Stack() :_size(0), _elem(new int[MAX]){}
	int top(){ return _elem[_size - 1]; }
	void push(int i)
	{//assert(_size < 1600,000)
		_elem[_size] = i;
		++_size;
	}
	int pop()
	{//assert(_size > 0)
		--_size;
		return _elem[_size];
	}
	int size(){ return _size; }
	bool empty(){ return !_size; }
};
class Queue
{
private:
	int _curr;
	int _size;
	bool *_elem;
public:
	Queue() :_curr(0),_size(0), _elem(new bool[2*MAX]){}
	bool top(){ return _elem[_curr]; }
	void push(bool flag)
	{ 
		_elem[_size++] = flag; 
	}
	bool pop()
	{
		return _elem[_curr++];
	}
	bool empty(){ return _curr >= _size; }
	int size(){ return _size - _curr; }
};

int main()
{
	int n, m;
	cin >> n >> m;
	Stack S;
	Queue P;
	int *B = new int[MAX];

	int a, i = 0;
	while (i < n && cin >> a)
		B[i++] = a;
	//A默认为{1,2,3,4,5...}

	i = 1;
	for (int j = 0; j < n; ++j)
	{//对B中自底向上寻找对应的A元素，共 n 次
		while (S.empty() || B[j] != S.top())
		{
			S.push(i++);
			P.push(true);
			if (m < S.size())
			{
				cout << "No";
				return 0;
			}
		}
		S.pop();
		P.push(false); 
	}
	if (!S.empty())
	{
		cout << "No";
		return 0;
	}
	i = P.size() + 1;
	while (0 < --i)
	{
		cout << (P.pop() ? "push" : "pop") << endl;
	}

	return 0;
}

