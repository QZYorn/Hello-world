#define _CRT_SECURE_NO_WARNINGS 1
#define _SCL_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
//#include<fstream>
//#include<iterator>
//#include<sstream>
#include<vector>
//#include<list>
#include<map>
#include<set>
//#include<deque>
//#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
#include<memory.h>
#include<stdlib.h>
using namespace std;
//using namespace std::placeholders;


struct X
{
	X()
	{
		cout << "X()" << endl;
	}
	X(const X&)
	{
		cout << "X(const X&)" << endl;
	}

	X& operator=(const X&x)
	{
		cout << "operator=" << endl;
		return *this;
	}

	~X()
	{
		cout << "~X()" << endl;
	}
};

void f1(const X){}
void f2(const X&){};

void test13_1_3()
{
	cout << "\n13.1.3" << endl;

	//13.13
	{
		cout << "非引用" << endl;
		X x;
		f1(x);
	}
	{
		cout << "引用" << endl;
		X x;
		f2(x);
	}
	{
		cout << "动态分配" << endl;
		auto x = new X;
		delete x;
	}
	{
		cout << "存入容器" << endl;
		vector<X> x;
		X x1;
		X x2;
		x.push_back(x1);
		cout << "x1" << endl;
		x.push_back(x2);
		cout << "x2" << endl;
	}

}

class Employee
{
public:
	Employee()
	{
		_digital = ++_num;
		cout << "默认构造函数 ->";
	}
	Employee(string const &s) :_name(s)
	{
		_digital = ++_num;
		cout << "字符串形参构造函数 ->";
	}
	Employee(const Employee& ep) :_name(ep._name)
	{
		_digital = ++_num;
		cout << "拷贝构造函数 ->";
	}
	Employee& operator=(const Employee& ep)
	{
		cout << "拷贝赋值操作 ->";
		this->_name = ep._name;
		this->_digital = ++_num;
		return *this;
	}
	~Employee() = default;

	int _digital;
	string _name;
private:
	static  int _num;
	

};
int Employee::_num = 0;

void test13_1_6()
{
	cout << "\n13.1.6" << endl;

	//13.18
	cout << "\nep1:";
	Employee ep1;
	cout << "\nep2:";
	Employee ep2("bbb");
	cout << "\nep3:";
	Employee ep3(ep2);
	cout << "\nep4:";
	Employee ep4 = ep3;
	cout << "\nep5:";
	Employee ep5;
	ep5 = ep4;
	cout << endl;

	cout << "ep1:name:" << ep1._name << "\tdigital:" << ep1._digital << endl;
	cout << "ep2:name:" << ep2._name << "\tdigital:" << ep2._digital << endl;
	cout << "ep3:name:" << ep3._name << "\tdigital:" << ep3._digital << endl;
	cout << "ep4:name:" << ep4._name << "\tdigital:" << ep4._digital << endl;
	cout << "ep5:name:" << ep5._name << "\tdigital:" << ep5._digital << endl;

}




void test13_3()
{
	cout << "\n13.3" << endl;

	//12.30
	HasPtr hp1("aaa");
	hp1.push_i(10);

	HasPtr hp2("ccc");
	hp2.push_i(20);

	cout << "hp1: " << (*hp1.getPs()) << "\t" << hp1.getI() << endl;
	cout << "hp2: " << (*hp2.getPs()) << "\t" << hp2.getI() << endl;
	
	swap(hp1, hp2);

	cout << "hp1: " << (*hp1.getPs()) << "\t" << hp1.getI() << endl;
	cout << "hp2: " << (*hp2.getPs()) << "\t" << hp2.getI() << endl;

	HasPtr hp3("ddd");
	hp3.push_i(60);
	HasPtr hp4("eee");
	hp4.push_i(5);
	vector<HasPtr> hvec;
	hvec.push_back(hp1);
	hvec.push_back(hp2);
	hvec.push_back(hp3);
	hvec.push_back(hp4);
	sort(hvec.begin(), hvec.end());
}




void test13_5()
{
	cout << "13.5:" << endl;

	//13.42
	StrVec sv;
	sv.push_back("a");
	sv.push_back("c");
	StrVec sv1{ "e", "w", "q" };
	StrVec sv2(sv1);
	StrVec sv3;
	StrVec sv4;
	sv3 = sv;
	sv2.reserve(10);
	sv3.resize(10, "j");
	sv4 = sv3;
	sv4.resize(2);

	cout << "sv: ";
	print(sv);
	cout << "  size:" << sv.size() << " capacity: " << sv.capacity() << endl;
	cout << "sv1: ";
	print(sv1);
	cout << "  size:" << sv1.size() << " capacity: " << sv1.capacity() << endl;
	cout << "sv2: ";
	print(sv2);
	cout << "  size:" << sv2.size() << " capacity: " << sv2.capacity() << endl;
	cout << "sv3: ";
	print(sv3);
	cout << "  size:" << sv3.size() << " capacity: " << sv3.capacity() << endl;
	cout << "sv4: ";
	print(sv4);
	cout << "  size:" << sv4.size() << " capacity: " << sv4.capacity() << endl;
}

int f()
{
	return 1;
}
void test13_6_1()
{
	vector<int> vi(100);
	int && r1 = f();
	int & r2 = vi[0];
	int & r3 = r1;
	int && r4 = vi[0] * f();
}


int main()
{
	//test13_1_3();
	//test13_1_6();
	//test13_3();
	//test13_5();
	//test13_6_1();
	return 0;
}