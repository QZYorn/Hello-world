#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
//#include<iterator>
#include<sstream>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
#include<memory>
using namespace std;
using namespace std::placeholders;


vector<int>* vei()
{
	return new vector<int>();
}

void print(vector<int>* vei_ptr)
{
	for (auto i : *vei_ptr)
		cout << i << " ";
}

void read(vector<int>* vei_ptr)
{
	int i;
	while (cin >> i)
	{
		vei_ptr->push_back(i);
	}
}

shared_ptr<vector<int>> vei_shared()
{
	return make_shared<vector<int>>();
}

void print_shared(shared_ptr<vector<int>> vei_ptr)
{
	for (auto i : *vei_ptr)
		cout << i << " ";
}

void read_shared(shared_ptr<vector<int>> vei_ptr)
{
	int i;
	while (cin >> i)
	{
		vei_ptr->push_back(i);
	}
}

void test12_1_2()
{
	cout << "\n12.1.2" << endl;

	//12.6
	auto vei_ptr = vei();
	if (!vei_ptr)
	{
		cout << "内存不足" << endl;
			return;
	}
	read(vei_ptr);
	print(vei_ptr);
	delete vei_ptr;
	vei_ptr = nullptr;

	//12.7
	auto vei_shared_ptr = vei_shared();
	if (!vei_shared_ptr)
	{
		cout << "内存不足" << endl;
		return;
	}
	read_shared(vei_shared_ptr);
	print_shared(vei_shared_ptr);
}

struct connection{};
struct destination{};
connection connect(destination* d)
{
	//cout << *d << endl;
	cout << "打开连接" << endl;
	return connection();
}
void disconnection(connection& c)
{
	//delete c;
	cout << "关闭连接" << endl;

}
void f(destination &d)
{
	connection c = connect(&d);
	//
	//
	//意外结束
	//cout << endl;
	disconnection(c);
}
void end_connection(connection* c){ disconnection(*c); }

void f2(destination &d)
{
	connection c = connect(&d);
	//12.14
	//shared_ptr<connection> p(&c, end_connection);
	//12.15
	shared_ptr<connection> p(&c, [](connection*pc){disconnection(*pc); });
}

void test12_1_5()
{
	cout << "\n12.1.5" << endl;

	int i = 0;
	unique_ptr<int> u1;
	unique_ptr<int> u2(new int(i));
	//unique_ptr<int> u3(u2);//拷贝构造
	//unique_ptr<int> u4 = u1;
	//u2 = u1;//赋值操作
}

void test12_1_6()
{
	cout << "\n12.1.6" << endl;

	ifstream ifs("test.txt");
	if (!ifs.is_open())
	{
		cout << "file can not open " << endl;
		return;
	}
	StrBlob sb;
	string s;
	while (ifs >> s)
	{
		sb.push_back(s);
	}
	
	for (auto it = sb.begin(); !it.eq(sb.end());it.incr())
	{
		cout << it.deref() << endl;
	}
	ifs.close();
}

void test12_2_1()
{
	cout << "\n12.2.1" << endl;

	//12.23
	char* chr_ptr = new char[10];
	strcpy(chr_ptr, "aaa");
	strcat(chr_ptr + strlen("aaa"), "ccc");
	/*for (auto it = chr_ptr; it != chr_ptr + 10; ++it)
	{
		cout << *it;
	}*/
	cout << chr_ptr << endl;
	delete[] chr_ptr;
	chr_ptr = nullptr;

	string s1{ "aaa2" };
	string s2{ "ccc2" };
	char* chr_ptr2 = new char[s1.size()+s2.size()];
	strcpy(chr_ptr2, (s1+s2).c_str());
	/*for (auto it = chr_ptr2; it != chr_ptr2 + s1.size() + s2.size(); ++it)
	{
		cout << *it;
	}*/
	cout << chr_ptr2 << endl;

	//12.24
	unique_ptr<char[]> up(new char[5]());
	//unique_ptr<char[]> nup;
	string s;
	while (cin >> s)
	{
		int old_size = sizeof(up.get());
		if (s.size() > old_size)
		{
			int new_size = s.size()*1.5;
			unique_ptr<char[]> nup(new char[new_size]);
			swap(nup,up);
		}
		strcpy(up.get(), s.c_str());
	}
	cout << up.get() << endl;

	//12.25
	int *pa = new int[10];
	delete[] pa;

}

void test12_2_2()
{
	cout << "\n12.2.2" << endl;

	//12.26
	allocator<string> al;
	auto const p = al.allocate(10);//首元素
	auto q = p;//尾元素
	string s;
	while (cin >> s && q != p + 10)
	{
		al.construct(q++, s);
	}
	const size_t size = q - p;
	while (q != p)
	{
		al.destroy(--q);
	}
	al.deallocate(p,10);
}



ostream& print(ostream& os, QueryResult& qr)
{
	os << qr.word << " occurs "
		<< qr.line->size() << (1 < qr.line->size() ? " times " : " time ")
		<< endl;
	for (auto c : *qr.line)
	{
		os << "\t(line" << c+1  << ")"
			<< (*qr.file)[c] << endl;
	}
	return os;
}

void runQuries(ifstream &infile)
{
	TextQuery tq(infile);
	while (true)
	{
		cout << "输入要查找的单词，或输入q退出: ";
		string s;
		if (!(cin >> s) || s == "q")
			break;
		print(cout, tq.query(s)) << endl;
	}
}

void test12_3_1()
{
	cout << "\n12.3.1" << endl;

	//12.27
	
}

int main()
{
	//test12_1_2();
	//test12_1_5();
	//test12_1_6();
	//test12_2_1();
	//test12_2_2();
	test12_3_1();
	return 0;
}