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
class Message;
class Floder
{
public:
	void addMsg(Message* mp);
	void remMsg(Message* mp);
private:
	set<Message*> message;
};

class Message
{
	friend class Floder;
public:
	Message(string value = " ") :contents(value){}
	Message(const Message& m);
	~Message(){ remove_from_Floder(); }

	Message& operator=(const Message& m);
	void save(Floder& f);
	void remove(Floder& f);
	void addFld(Floder *fp);
	void remFld(Floder *fp);

private:
	string contents;
	set<Floder*> floder;

	void add_to_Floder(const Message& m);//拷贝后，本message应加入 目标message所在的每个floder中
	void remove_from_Floder();//从本message所在的每个floder中删去本message
};

Message::Message(const Message& m):
	contents(m.contents), floder(m.floder)
{
	//本对象为拷贝构造出来的，与源对象共享源目录，源目录均应插入本对象
	add_to_Floder(m);
}

Message& Message::operator=(const Message& m)
{
	remove_from_Floder();//本对象所在目录均删去本对象地址
	this->contents = m.contents;
	this->floder = m.floder;
	add_to_Floder(m);
	return *this;
}

void Message::save(Floder& f)
{
	floder.insert(&f);//本对象所在目录增加
	f.addMsg(this);//目录中添加到本对象的地址
}

void Message::remove(Floder& f)
{
	floder.erase(&f);
	f.remMsg(this);
}

void Message::addFld(Floder *fp)
{
	floder.insert(fp);
	fp->addMsg(this);
}
void Message::remFld(Floder *fp)
{
	floder.erase(fp);
	fp->remMsg(this);
}

void Message::add_to_Floder(const Message& m)
{
	for (auto f : m.floder)
	{
		f->addMsg(this);
	}
}
void Message::remove_from_Floder()
{
	for (auto f : this->floder)
	{
		f->remMsg(this);
	}
}
void Floder::addMsg(Message* mp)
{
	message.insert(mp);
}
void Floder::remMsg(Message* mp)
{
	message.erase(mp);
}

class StrVec
{
public:
	StrVec() ://默认构造
		elements(nullptr), first_free(nullptr), cap(nullptr){}
	StrVec(initializer_list<string> ini_list);
	StrVec(const StrVec& sv);//拷贝构造
	StrVec& operator=(const StrVec& sv);//拷贝赋值
	~StrVec();//析构

	void push_back(const string &s);
	size_t  size()	  const{ return first_free - elements; }
	size_t  capacity()const{ return cap - elements; }
	string* begin()   const{ return elements; }
	string* end()	  const{ return first_free; }
	void reserve(const size_t si);
	void resize(const size_t si, string s = "");
private:
	static allocator<string> alloc;

	pair<string*,string*> alloc_n_copy(const string* b,const string* e);//分配内存，并拷贝给定范围内元素
	void chk_n_alloc(){ if (size() == capacity()) reallocate(0); }//检查剩余空间并根据情况分配内存
	void free();	   //销毁构造的元素并释放内存
	void reallocate(size_t si); //分配新内存

	string *elements;   //内存中的首元素
	string *first_free;//最后一个实际元素之后的位置
	string *cap;	   //分配的内存尾后位置
};
allocator<string> StrVec::alloc;

StrVec::StrVec(initializer_list<string> ini_list)
{
	auto newdata = alloc_n_copy(ini_list.begin(), ini_list.end());
	elements = newdata.first;
	cap = first_free = newdata.second;
}

StrVec::StrVec(const StrVec& sv)
{
	auto newdata = alloc_n_copy(sv.begin(), sv.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
StrVec& StrVec::operator=(const StrVec& sv)
{
	auto data = alloc_n_copy(sv.begin(), sv.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
StrVec::~StrVec()
{
	free();
}
void StrVec::push_back(const string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++,s);
}

void StrVec::reserve(const size_t si)
{
	reallocate(si);
}
void StrVec::resize(const size_t si,string s)
{
	if (size() < si)
	{
		if (capacity() < si)
		{
			reallocate(si);
		}
		for (size_t b = size(); b < si; ++b)
			alloc.construct(first_free++, s);
	}
	else if (si < size())
	{
		for (size_t b = size();si < b; --b)
			alloc.destroy(--first_free);
	}
}

pair<string*, string*> 
StrVec::alloc_n_copy(const string* b, const string* e)
{
	auto data = alloc.allocate(e - b);
	return{ data, uninitialized_copy(b, e, data) };
}

void StrVec::free()
{
	if (elements != nullptr)
	{
		for_each(elements, first_free, [](string& s){alloc.destroy(&s); });
		/*for (auto p = first_free - 1; p != elements; --p)
		{
			alloc.destroy(p);
		}*/
		alloc.deallocate(elements,cap - elements);
	}
}
void StrVec::reallocate(size_t si)
{
	auto newcapacity = si;
	if (si <= size())
		newcapacity = size() ? size() * 2 : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
	{
		alloc.construct(dest++, move(*elem++));
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = newdata + newcapacity;
}

void print(StrVec& sv)
{
	for (auto i : sv)
		cout << i << " ";
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
	test13_6_1();
	return 0;
}