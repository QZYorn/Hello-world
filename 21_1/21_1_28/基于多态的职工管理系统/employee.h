#pragma once
#include<iostream>
#include"worker.h"

using namespace std;


class Employee :public Worker//Ա����
{
public:
	Employee(int id, string name, int dId);
	virtual void ShowInfo();
	virtual string getDeptName();
};