#pragma once
#include<iostream>
#include"worker.h"

using namespace std;


class Boss :public Worker//Ա����
{
public:
	Boss(int id, string name, int dId);
	virtual void ShowInfo();
	virtual string getDeptName();
};