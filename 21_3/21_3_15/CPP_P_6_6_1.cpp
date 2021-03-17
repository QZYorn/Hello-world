#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;
#include<iostream>
#include<string>
#include<vector>

void test4_10()
{
	//4.32
	const int size = 5;
	int ia[size] = { 1, 2, 3, 4, 5 };
	for (int *ptr = ia, ix = 0; //初始化ptr指向ia首元素，ix = 0
		ix != size && ptr != ia + size;//ix不超过ia大小 并且 ptr不指向ia末元素
		++ix, ++ptr)//ix+1，ptr指向下一个元素
	{
		;
	}

	//4.35
	int ival = -5;
	unsigned int ui = 10;
	float fval = -3.14;
	double dval = -1.234;

	//dval = ui * fval;

	//auto a = ival * 1.0;
	//fval = ui - a;

	//ival *= dval;

	////4.37
	//int i = 3;
	//double d;
	//const string *ps;
	//char *pc;
	//void *pv;
	////a
	//pv = (void*)ps;
	//pv = const_cast<string*> (ps);

	////b
	//i = int(*pc);
	//i = static_cast<int>(*pc);

	////c
	//pv = &d;
	//pv = static_cast<void*>(&d);

	////d
	//pc = (char*)pv;
	//pc = static_cast<char*>(pv);

	////int i = 3;
	//switch (i)
	//{
	////case 11,3,5,7:
	//default:
	//	break;
	//}
}

void test5_4_1()
{
	string s1;
	string s2;
	string sm;
	int num = 1;
	int maxNum = 0;

	cin >> s1;
	while (cin >> s2)
	{
		if (s1 == s2)
		{
			num++;
		}
		else
		{
			if (maxNum < num)
			{
				maxNum = num;
				sm = s1;
				num = 1;
			}
			s1 = s2;
			
			
		}
	}
	cout << sm << " " << maxNum;

	
}

void test5_4_4()
{
	//5.18
	//5.23
	int a, b;
	while (cin >> a >> b)
	{
		try
		{

			if (b == 0)
				throw runtime_error("Int divition by zero");
			cout << a / b << endl;
		}
		catch (runtime_error err)
		{
			cout << err.what()
				<< "\nTry again ? Entry y or n" << endl;
			char c;
			cin >> c;
			if (c != 'y')
				break;
		}
	}
}

int fact(int i)
{
	
	if (i == 1)
		return 1;
	return fact(i - 1)*i;
}

int staticInt()
{
	static int a = 0;
	a++;
	return a;
}

void reset(int &i)
{
	i = 0;
}

void test6_1()
{
	//6.3
	int i;
	cin >> i;
	cout << "阶乘结果：" <<  fact(i) << endl;

	//6.6
	int j = 0;
	while (0 <= --i)
	{
		j = staticInt();
	}
	cout << "static调用次数:" <<  j << endl;
}

//int count(const string &, char);

int max(const int a, const int *pb)
{
	if (a < *pb)
		return *pb;
	return a;
}

void myswap(int *&pa, int *&pb)
{
	int *mid = pa;
	pa = pb;
	pb = mid;
}

int mysum(initializer_list<int> li)
{
	int sum = 0;
	for (auto i : li)
		sum += i;
	return sum;

}
typedef string strarr[10];

string(&trytrytry())[10];
strarr &trytrytry1();
auto trytrytry2()->string(&)[10];
string str[10];
decltype(str) &trytrytry3();



typedef int intarr[10];

int(&trytrytryi())[10];
intarr &trytrytryi1();
auto trytrytryi2()->int(&)[10];
int iarr[10];
decltype(iarr) &trytrytryi3();


void f()
{
	cout << "f()" << endl;
}

void f(int)
{
	cout << "f(int)" << endl;
}

void f(int, int)
{
	cout << "f(int,int)" << endl;
}

void f(double, double = 3.14)
{
	cout << "f(double,double = 3.14)" << endl;
}


void test6_2_2()
{
	//6.11
	int a = 10;
	int &b = a;
	reset(b);
	cout << "b = " << b << endl;
	//count("aaaaa", 'a');

	int c = 50;
	int *pc = &c;
	int *pa = &a;
	cout << max(a, pc) << endl;
	myswap(pa, pc);
	cout << "*pa = " << *pa << "  *pc = " << *pc << endl;

	//f(2.56, 42);
	f(42);
	f(42, 0);
	f(2.56, 3.14);
}

int main()
{
	//test4_10();
	//test5_4_1();
	//test5_4_4();
	//test6_1();
	test6_2_2();
	return 0;
}