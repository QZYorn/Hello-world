#define _CRT_SECURE_NO_WARNINGS 1
#define _SCL_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
//#include<iterator>
#include<sstream>
#include<vector>
//#include<list>
//#include<map>
//#include<set>
//#include<deque>
//#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
#include<memory>
//#include<stdlib.h>
#include<tuple>
#include<bitset>
#include<random>
#include<ctime>
#include<iomanip>
#include"Sales_data.h"
using namespace std;
//using namespace std::placeholders;

namespace Ex{
	int ivar = 0;
	double dvar = 0;
	const int limit = 1000;
}
int ivar = 0;



void test18()
{
	////18.10
	//Sales_data sd1("aaa", 10, 5);
	//Sales_data sd2("bbb", 10, 5);
	////sd1 + sd2;
	//try{
	//	sd1 + sd2;
	//}
	//catch (const isbn_mismatch &e)
	//{
	//	cerr << e.what() << " left isbn(" << e.left
	//	     << ") right isbn(" << e.right << ")" << endl;
	//}

	//18.16
	//Î»ÖÃ2
	/*using Ex::dvar;
	using Ex::ivar;
	using Ex::limit;*/
	using namespace Ex;
	double dvar = 3.1416;
	int iobj = limit + 1;
	//++ivar;
	++::ivar;
}

int main()
{
	test18();
	return 0;
}