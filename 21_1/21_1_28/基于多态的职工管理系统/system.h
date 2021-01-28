#pragma once
#include<iostream>
#include<string>
#include<assert.h>
#include<fstream>

#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

#define FILENAME "workerFILE.txt"

class System
{
public:
	//行为
	System();
	void Menu();//菜单显示
	void Exit();//退出提示
	void Add_Wok();	 //添加
	void Show_Work();//显示
	void Del_Work(); //删除
	void Mod_Work(); //修改
	void Find_Work();//查找 编号 或 姓名
	void Sort_Work();//排序
	void Clean_Work();//清空
	void Delete_Arr();//指针数组释放 以及 每个堆区指针释放
	void Save();//保存到文件中
	int getNum();  //获取文件中职工数并返回
	void InitArr();//初始化指针数组，将文件中职工数据读取到指针数组里
	int IsExist(int id);//接收编号，根据编号查找职员是否存在，返回角标
	~System();

	//属性
	Worker **m_workArr;//维护指针数组，每个指针指向某个职工
	int m_workNum;//当前存有的职工数
	bool FileIsEmpty;//判断文件是否为空
};