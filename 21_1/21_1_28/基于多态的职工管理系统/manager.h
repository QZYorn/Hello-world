#pragma once
#include<iostream>
#include"worker.h"

using namespace std;


class Manager :public Worker//‘±π§¿‡
{
public:
	Manager(int id, string name, int dId);
	virtual void ShowInfo();
	virtual string getDeptName();
};