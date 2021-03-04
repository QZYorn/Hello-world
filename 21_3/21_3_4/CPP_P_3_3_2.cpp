#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<vector>
using namespace std;
typedef double MyDouble;
using size_t = unsigned int;

void test2_3_2()
{
	//2.3.2

	//int *p = nullptr;
	int i = 0;
	//double* dp = &i;
	//int *ip = i;
	void *p = &i;
	//*p = 5;
	//i = *p + 10;
	*(int*)p = 5;
	i = *(int*)p + 10;
}

void test2_3_3()
{
	//2.25

	//指针，整形，引用
	//int* ip, i, &r = i;

	//整形，指针
	//int i, *ip = 0;

	//指针，整形
	int* ip, ip2;
}

void test2_4()
{
	//2.26

	//非法，未初始化
	//const int buf;

	int cnt = 0;

	const int sz = cnt;

	++cnt;
	//++sz;
}

void test2_4_2()
{
	//2.27

	int i = -1;// &r = 0;
	const int i2 = i, &r = i;
	//非法，常量指针，const point
	//int *const p2 = &i2;
	//合法，常量引用可绑定字面值常量
	const int f = -1, &t = 0;
	const int *const p4 = &i2;
	//const int *p1 = &i2;
	//const int &const r2;

	//2.28
	//非法，常量指针，等价引用，需设定初始值
	int x = 100; //*const cp;
	//同上
	int *p1, *const p2 = &x;
	//常量需设定初始值
	const int ic = 16,&q = ic;
	const int *const p3 = &ic;
	//合法，指向常量的指针，pointer to const
	const int *p;

	//2.29
	x = ic;
	//p1不可接常量
	//p1 = p3;
	//p1不可接常量
	//p1 = &ic;
	//p3不可改
	//p3 = &ic;
	//p2不可修改
	//p2 = p1;
	//ic不可修改
	//ic = *p3;
}

void test2_4_3()
{
	//2.30
	int i = 0;
	//顶层const
	const int v2 = 0;
	//仅拷贝值
	int v1 = v2;
	//整型指针p1指向整型v1,引用r1绑定整型v1
	int *p1 = &v1, &r1 = v1;
	//底层const，pointer to const p2指向整型常量v2,
	const int *p2 = &v2, 
		//底层且顶层const，p3指向i，指针指向不可修改，值不可修改
		*const p3 = &i, 
		//常量引用，对const的引用，r2绑定整型常量v2
		&r2 = v2;

	//2.31
	//r1绑定的v1，所以等同 v1 = v2
	r1 = v2;
	//底层const不匹配,p1非底层const
	//p1 = p2;
	//int可以转为const int
	p2 = p1;
	//底层const不匹配
	//p1 = p3;
	//底层const 接 底层顶层const
	p2 = p3;
	
}

void test2_4_4()
{
	//非法，因为指针不可直接赋值常量
	//int null = 0, *p = null;
	//合法，null为常量表达式，编译时就将作用域内null全部替换为0了
	const int null = 0;
	int *p = null;
}

void test2_5_2()
{
	//2.33
	int i = 0, &r = i;
	auto a = r;
	const int ci = i, &cr = ci;
	auto b = ci;
	auto c = cr;
	auto d = &i;
	auto e = &ci;
	auto &g = ci;
	
	a = 42;
	b = 42;
	c = 42;
	//d = 42;指针不可直接赋值整型
	//e = 42;
	//g = 42;

	//2.35
	const int x = 42;
	auto j = x;
	const auto &k = x;
	auto *p = &x;
	const auto j2 = x, &k2 = x;
}

void test2_5_3()
{
	const int i = 42, *p = &i, &r = i;
	decltype(i + 0) q;
	decltype(p) f;
	//表达式结果为左值则返回引用
	//decltype(*p) e;

	//2.36
	int a = 3, b = 4;
	decltype(a) c = a;
	decltype((b)) d = a;//绑定a
	++c;//c = 4
	++d;//a = d = 4
}

void test3_2_2()
{
	//3.2
	string line;
	getline(cin, line);
	cout << line << endl;

	while (cin >> line)
	{
		cout << line << endl;
	}


}

void test3_2_3()
{
	//3.6
	string str(10, 'a');
	for (char &c : str)
		c = 'X';
	for (auto c : str)
		cout << c;
	cout << endl;

	//3.10
	string str2;
	char ctmp;
	while (cin >> ctmp)
	{
		if (!ispunct(ctmp))
			str2 += ctmp;
	}
	cout << str2 << endl;
	//aa,c.c<!gg:rr'"ww[}tt(jj)i/kk?

	//3.11
	const string s = "Keep out!";
	for (auto &c : s)
		cout << c;
		//c = 'a';
}

void test3_3_1()
{
	//3.12
	vector<vector<int>> ivec;
	//vector<string> svec = ivec;
	vector<string> svec(10, "null");

	//3.13
	vector<int> v1;
	vector<int> v2(10);//10个0
	vector<int> v3(10, 42);//10个42
	vector<int> v4{ 10 };//一个10
	vector<int> v5{ 10, 42 };//一个10一个42
	vector<string> v6{ 10 };//10个空串
	vector<string> v7{ 10, "hi" };//10个hi
}

void test3_3_2()
{
	//3.14
	int i;
	vector<int> iv;
	while (cin >> i)
	{
		iv.push_back(i);
	}
	for (auto it : iv)
		cout << it;
}

int main()
{
	test2_3_2();
	test2_3_3();
	test2_4();
	test2_4_2();
	test2_4_3();
	test2_4_4();
	test2_5_2();
	test2_5_3();

	//test3_2_2();
	//test3_2_3();
	test3_3_1();
	test3_3_2();


	return 0;
}