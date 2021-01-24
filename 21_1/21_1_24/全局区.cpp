#include<iostream>
using namespace std;
int g_a = 10;
int g_b = 10;
static int s_g_a = 10;
static int s_g_b = 10;
const int c_g_a = 10;
int main()
{
	int a = 10;
	int b = 20;
	cout << "a \t= " << &a << endl;
	cout << "b \t= " << &b << endl;
	cout << "g_a \t= " << &g_a << endl;
	cout << "g_b \t= " << &g_b << endl;
	cout << "s_g_a \t= " << &s_g_a << endl;
	cout << "s_g_b \t= " << &s_g_b << endl;
	static int s_l_a = 10;
	static int s_l_b = 10;
	cout << "s_l_a \t= " << &s_l_a << endl;
	cout << "s_l_b \t= " << &s_l_b << endl;
	cout << "×Ö·û´® \t= " << &"helloworld" << endl;
	const int c_l_a = 10;
	cout << "c_g_a \t= " << &c_g_a << endl;
	cout << "c_l_a \t= " << &c_l_a << endl;
	system("pause");
	return 0;
}