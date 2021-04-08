#pragma once

#include<iostream>
#include<string>
#include<map>
using namespace std;

class Vehicle
{
	friend ostream& operator<<(ostream& os, const Vehicle& vcl);
	friend istream& operator>>(istream& is, Vehicle& vcl);
	friend Vehicle operator+(const Vehicle& l_vcl, const Vehicle& r_vcl);
	friend bool operator==(const Vehicle& l_vcl, const Vehicle& r_vcl);
	friend bool operator!=(const Vehicle& l_vcl, const Vehicle& r_vcl);
	explicit operator bool(){ return (_name_no == make_pair(string(),string())) && (_count == 0) && (_price < 0.0001); }


public:
	Vehicle() :_count(0), _price(0){}
	Vehicle(string name, string no, unsigned int count, double price)
		:_name_no(make_pair(name, no)),_count(count),_price(price){}

	Vehicle& operator=(const Vehicle& vcl);//拷贝赋值
	Vehicle& operator=(Vehicle&& vcl);//移动赋值
	Vehicle& operator+=(const Vehicle& vcl);

private:
	pair<string,string> _name_no;//车名&车的编号
	unsigned int _count;//车辆数
	double _price;//每辆车的价格
};

ostream& operator<<(ostream& os, const Vehicle& vcl)
{
	os << vcl._name_no.first << " " << vcl._name_no.second << " "
		<< vcl._count << " " << vcl._price;
	return os;
}
istream& operator>>(istream& is, Vehicle& vcl)
{
	is >> vcl._name_no.first >> vcl._name_no.second 
		>> vcl._count >> vcl._price;
	if (!is)
	{
		vcl = Vehicle();
	}
	return is;
}

Vehicle operator+(const Vehicle& l_vcl, const Vehicle& r_vcl)
{
	Vehicle	sum = l_vcl;
	sum += r_vcl;
	return sum;
}

Vehicle& Vehicle::operator=(const Vehicle& vcl)//拷贝赋值
{
	_name_no = vcl._name_no;
	_count = vcl._count;
	_price = vcl._price;
	return *this;
}
Vehicle& Vehicle::operator=(Vehicle&& vcl)//移动赋值
{
	_name_no = move(vcl._name_no);
	_count = vcl._count;
	_price = vcl._price;
	return *this;
}


Vehicle& Vehicle::operator+=(const Vehicle& vcl)
{
	this->_price = (vcl._price*vcl._count + this->_price*this->_count)
		/ (vcl._count + this->_count);
	this->_count += vcl._count;
}

bool operator==(const Vehicle& l_vcl, const Vehicle& r_vcl)
{
	return l_vcl._name_no == r_vcl._name_no&&
		l_vcl._count == r_vcl._count&&
		l_vcl._price == r_vcl._price;
}
bool operator!=(const Vehicle& l_vcl, const Vehicle& r_vcl)
{
	return!(l_vcl == r_vcl);
}
