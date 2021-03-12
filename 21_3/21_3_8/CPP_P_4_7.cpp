#define _CRT_SECURE_NO_WARNINGS 1	
#include<vector>
#include<iostream>
#include<string>
using namespace std;

string sa[10];
int iia[10];
int a;

void test3_3_3()
{
	//3.17
	vector<string> v;
	string st;
	while (cin >> st)
	{
		for (char &c : st)
			c = toupper(c);
		v.push_back(st);
	}
	
	for (const string s : v)
		cout << s << endl;

	//3.18
	vector<int> ivec;
	//ivec[0] = 42;
	ivec.push_back(42);

	//3.20
	cin.clear();
	vector<int> ivec2;
	int i;
	while (cin >> i)
	{
		ivec2.push_back(i);
	}
	for (auto it = ivec2.begin(); it != ivec2.end()-1; ++it)
	{
		cout << *it + *(it + 1) << " ";
	}

	for (auto lit = ivec2.begin(),rit = ivec2.end() - 1; lit != rit; ++lit,--rit)
	{
		cout << *lit + *rit << " ";
		if (lit+1 == rit - 1)
		{
			cout << (*(lit + 1)) * 2 << " ";
		}
	}
}

void test3_5_1()
{
	//3.27
	unsigned buf_size = 1024;
	//int ia[buf_size];
	int ia[4 * 7 - 14];

	//3.28
	cout << sa[0] << iia[0] << a << endl;
	string sa[10];
	int iia[10];
	int a = 0;
	cout << sa[0] << iia[0] << a << endl;


	
}

void test3_5_3()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int *p1 = &arr[5];
	int *p2 = &arr[0];

	//p1 += p2 - p1;
	p2 += p1 - p2;

}

void test3_5_4()
{
	//3.37
	const char ca[] = { 'h', 'e', 'l', 'l', 'o' };
	const char *cp = ca;
	//while (*cp)
	{
		cout << *cp << endl;
		++cp;
	}//即便超出数组也会一直输出直到遇到空字符
	
	//3.40
	const char c1[] = "Hello ";
	const char c2[] = "World";
	char c3[13];
	strcpy(c3, c1);
	strcat(c3, c2);

	//3.41
	int ivec[10];
	vector<int> vec(begin(ivec), end(ivec) - 2);

	auto it = vec.begin();
	int i = 0;
	while (it != vec.end())
	{
		ivec[i++] = *it;
		++it;
	}

}

void test3_6()
{
	int ia[3][4];
	int i = 0;
	for (int (&row)[4] : ia)
	{
		for (int &col : row)
			col = ++i;
	}

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			++ia[row][col];
		}
	}

	for (int(*ber)[4] = begin(ia); ber < end(ia); ++ber)
	{
		for (int *bec = begin(*ber); bec < end(*ber); ++bec)
		{
			cout << *bec << " ";
		}
		cout << endl;
	}
}

void test4_4()
{
	//4.15
	double dval;
	int iival;
	int *pi;

	dval = iival = 0;
	pi = 0;

	//4.16
	int p;
	if ((p = iival) == 0)
		cout << p << endl;

	//4.17
	int arr[] = { 1, 10, 20, 30 };
	int *ap = arr;
	cout << *ap++ << " ";//1
	cout << --*ap << " ";//9
	cout << *++ap << " ";//20
	cout << (*ap)-- << " ";//19

	//4.19
	int *ptr = arr;
	vector<int> vec = {7,77,777};
	int ival = 99;
	ptr != 0 && *ptr++;//先判断ptr是否为空指针，然后判断ptr是否指向0，ptr先后移动一步
	ival++ && ival;//先判断ival是否为零，ival+1,再判断ival是否为零
	vec[ival++] <= vec[ival];//求值顺序不一定，未知行为

	//4.20
	vector<string>::iterator it;
	*it++;//先解引用迭代器得到字符串，返回字符串，再把迭代器向后移动一位
	//(*it)++;//非法，先解引用得到字符串，再把字符串+1
	//*it.empty();//非法，先试图访问迭代器的empty()函数，再对返回值解引用
	it->empty();//访问字符串的empty()函数
	//++*it;//非法，先对迭代器解引用得到字符串，再对字符串+1，返回字符串
	it++->empty();//访问字符串的empty()函数，迭代器向后一位

}

void test4_7()
{
	//4.21
	vector<int> ivec1 = { 1, 2, 3, 4, 5, 6, 7 };

	for (auto &it : ivec1)
		it % 2 ? it *= 2: it;

	//4.22
	int grade = 0;
	string finalGrade;
	finalGrade = (90 < grade) ? "high pass"
		: (75 < grade) ? "pass"
		: (60 < grade) ? "low pass"
		: "fail";

	if (90 < grade)
		finalGrade = "high pass";
	else if (75 < grade)
		finalGrade = "pass";
	else if (60 < grade)
		finalGrade = "low pass";
	else
		finalGrade = "fail";

	//4.23
	string s = "world";
	string p1 = s + (s[s.size() - 1] == 's' ? "" : "s");

}

void test4_8()
{
	//4.27
	unsigned long u11 = 3, u12 = 7;//0011  0111
	cout << (u11 & u12)  << " ";//0011  3
	cout << (u11 | u12)  << " ";//0111  7
	cout << (u11 && u12) << " ";//1
	cout << (u11 || u12) << endl;//1

	//4.28
	cout << sizeof(bool) << " "//1
		<< sizeof(char) << " "//1
		<< sizeof(short) << " "//2
		<< sizeof(unsigned short) << " "//2
		<< sizeof(int) << " "//4
		<< sizeof(unsigned int) << " "//4
		<< sizeof(long) << " "//4
		<< sizeof(unsigned long) << " "//4
		<< sizeof(long long) << " "//8
		<< sizeof(unsigned long long) << " "//8
		<< sizeof(float) << " "//4
		<< sizeof(double) << " "//8
		<< sizeof(long double) << endl;//8

	//4.29
	int x[10];
	int *p = x;
	cout << sizeof(x) / sizeof(*x) << endl;//40/4
	cout << sizeof(p) / sizeof(*p) << endl;//4/4

	//4.30
	int i = 0;
	int j = 0;
	int a = sizeof i + j;
	a = sizeof (i + j);

}



int main()
{
	//test3_3_3();
	//test3_5_1();
	//test3_5_3();
	//test3_5_4();
	//test3_6();
	//test4_4();
	//test4_7();
	test4_8();
	return 0;
}