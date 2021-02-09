#pragma once
#include<iostream>
using namespace std;
#include<map>
#include<string>
#include<fstream>
#include"globalFile.h"

class OrderFile
{
public:
	OrderFile();//构造函数

	void updateOrder();//更新预约信息
	
	//记录预约记录的容器
	//第一层key int为记录条数，第一层value map为具体的键值对信息
	//第二层key string为信息类别，第二层value string为具体信息
	map<int, map<string, string>> m_orderData;

	int m_Size;//预约记录条数
};