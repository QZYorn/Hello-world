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
	
}

int main()
{
	//test4_10();
	//test5_4_1();
	test5_4_4();
	return 0;
}