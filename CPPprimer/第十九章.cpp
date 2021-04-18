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
#include<exception>
#include"Sales_data.h"
using namespace std;
//using namespace std::placeholders;

//19.1
void *operator new(size_t size)
{
	if (void *men = malloc(size))
	return men;
	else
		throw bad_alloc();
}
void operator delete(void *men) 
{
	free(men);
}

void test19()
{
	//19.1

}

int main()
{
	test19();
	return 0;
}