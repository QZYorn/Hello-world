#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<time.h>
#include<random>
#include"Vector.hpp"
#include"List.hpp"
#include"Queue.hpp"	
#include"Stack.hpp"
#include"BinTree.hpp"
#include"GraphMatrix.hpp"

using namespace std;


int main()
{
	Vector<int> ivec(10);
	List<int> ilis;
	Queue<int> ique;
	Stack<int> istk;
	GraphMatrix<char, float> gm;
	gm.insert('a');
	cout << gm.vertex(0) << endl;
	return 0;
}