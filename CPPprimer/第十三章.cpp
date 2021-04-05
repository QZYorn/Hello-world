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

class HasPtr
{
	friend void swap(HasPtr& lh, HasPtr& rh);

public:

	HasPtr(const string & s = string()) :
		ps(new string(s)), i(0){}
	HasPtr(const HasPtr& hs) :ps(new string(*hs.ps)), i(hs.i){}
	
	HasPtr& operator=(const HasPtr& hs)
	{
		if (this == &hs)
			return *this;
		delete ps;
		ps = new string(*hs.ps);
		i = hs.i;
		return *this;
	}

	bool operator<(const HasPtr& hs)
	{
		return this->i < hs.i;
	}

	void push_i(int a)
	{
		this->i = a;
	}

	string* getPs()
	{
		return ps;
	}
	int getI()
	{
		return i;
	}

	~HasPtr()
	{
		delete ps;
	}
private:
	string *ps;
	int i;
};

inline
void swap(HasPtr& lh, HasPtr& rh)
{
	swap(lh.ps, rh.ps);
	swap(lh.i, rh.i);
	cout << "HasPtr swap" << endl;
}

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

class HasPtrp
{
public:
	HasPtrp(const string & s = string()) :
		ps(new string(s)), i(0),use(new int(1)){}
	HasPtrp(const HasPtrp& hs) :
		ps(hs.ps), i(hs.i), use(hs.use)
	{
		++*use;
	}

	HasPtrp& operator=(const HasPtrp& hs)
	{
		++*hs.use;//运算符右侧引用计数器递增
		if (--*use == 0)//运算符左侧引用计数器递减，若为零则释放内存
		{
			delete ps;
			delete use;
		}
		use = hs.use;
		i = hs.i;
		ps = hs.ps;
		return *this;
	}

	~HasPtrp()
	{
		if (--*use == 0)
		{
			delete ps;
			delete use;
		}
		
	}
private:
	string *ps;
	int i;
	int *use;//记录在使用对象数
};

class TreeNode
{
public:
	TreeNode()
		:value(string()), count(0), left(nullptr),right(nullptr),use(new int(1)){}
	TreeNode(const TreeNode& tn)
		:value(tn.value), count(tn.count), left(tn.left), right(tn.right), use(tn.use)
	{
		++*use;
	}

	TreeNode& operator=(const TreeNode& tn)
	{
		++*tn.use;
		if (--*this->use == 0)
		{
			delete left;
			left = nullptr;
			delete right;
			right = nullptr;
			delete use;
		}
		value = tn.value;
		count = tn.count;
		left = tn.left;
		right = tn.right;
		use = tn.use;
	}

	~TreeNode()
	{
		if (--*use == 0)
		{
			if (left != nullptr)
				delete left;
			if (right != nullptr)
				delete right;
			delete use;
		}
	}

private:
	string value;
	int count;
	TreeNode *left;
	TreeNode *right;
	int *use;
};


class BinStrTree
{
public:
	BinStrTree() :root(nullptr){}
	BinStrTree(const BinStrTree& bst) :root(new TreeNode(*bst.root)){}
	BinStrTree& operator=(const BinStrTree& bst)
	{
		if (&bst == this)
		{
			return *this;
		}
		delete root;
		root = new TreeNode(*bst.root);
	}
	~BinStrTree()
	{
		delete root;
	}
private:
	TreeNode *root;
};

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

int main()
{
	//test13_1_3();
	//test13_1_6();
	test13_3();
	return 0;
}