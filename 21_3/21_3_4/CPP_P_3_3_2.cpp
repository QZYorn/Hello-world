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

	//ָ�룬���Σ�����
	//int* ip, i, &r = i;

	//���Σ�ָ��
	//int i, *ip = 0;

	//ָ�룬����
	int* ip, ip2;
}

void test2_4()
{
	//2.26

	//�Ƿ���δ��ʼ��
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
	//�Ƿ�������ָ�룬const point
	//int *const p2 = &i2;
	//�Ϸ����������ÿɰ�����ֵ����
	const int f = -1, &t = 0;
	const int *const p4 = &i2;
	//const int *p1 = &i2;
	//const int &const r2;

	//2.28
	//�Ƿ�������ָ�룬�ȼ����ã����趨��ʼֵ
	int x = 100; //*const cp;
	//ͬ��
	int *p1, *const p2 = &x;
	//�������趨��ʼֵ
	const int ic = 16,&q = ic;
	const int *const p3 = &ic;
	//�Ϸ���ָ������ָ�룬pointer to const
	const int *p;

	//2.29
	x = ic;
	//p1���ɽӳ���
	//p1 = p3;
	//p1���ɽӳ���
	//p1 = &ic;
	//p3���ɸ�
	//p3 = &ic;
	//p2�����޸�
	//p2 = p1;
	//ic�����޸�
	//ic = *p3;
}

void test2_4_3()
{
	//2.30
	int i = 0;
	//����const
	const int v2 = 0;
	//������ֵ
	int v1 = v2;
	//����ָ��p1ָ������v1,����r1������v1
	int *p1 = &v1, &r1 = v1;
	//�ײ�const��pointer to const p2ָ�����ͳ���v2,
	const int *p2 = &v2, 
		//�ײ��Ҷ���const��p3ָ��i��ָ��ָ�򲻿��޸ģ�ֵ�����޸�
		*const p3 = &i, 
		//�������ã���const�����ã�r2�����ͳ���v2
		&r2 = v2;

	//2.31
	//r1�󶨵�v1�����Ե�ͬ v1 = v2
	r1 = v2;
	//�ײ�const��ƥ��,p1�ǵײ�const
	//p1 = p2;
	//int����תΪconst int
	p2 = p1;
	//�ײ�const��ƥ��
	//p1 = p3;
	//�ײ�const �� �ײ㶥��const
	p2 = p3;
	
}

void test2_4_4()
{
	//�Ƿ�����Ϊָ�벻��ֱ�Ӹ�ֵ����
	//int null = 0, *p = null;
	//�Ϸ���nullΪ�������ʽ������ʱ�ͽ���������nullȫ���滻Ϊ0��
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
	//d = 42;ָ�벻��ֱ�Ӹ�ֵ����
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
	//���ʽ���Ϊ��ֵ�򷵻�����
	//decltype(*p) e;

	//2.36
	int a = 3, b = 4;
	decltype(a) c = a;
	decltype((b)) d = a;//��a
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
	vector<int> v2(10);//10��0
	vector<int> v3(10, 42);//10��42
	vector<int> v4{ 10 };//һ��10
	vector<int> v5{ 10, 42 };//һ��10һ��42
	vector<string> v6{ 10 };//10���մ�
	vector<string> v7{ 10, "hi" };//10��hi
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