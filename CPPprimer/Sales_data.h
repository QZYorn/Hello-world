#pragma once

#include<string>
#include<iostream>
#include<unordered_set>
#include<exception>
using namespace std;

class out_of_stock :public runtime_error//自定义异常类，某些顺序无法满足
{
public:
	explicit out_of_stock(const string &s) :
		runtime_error(s){}
};
class isbn_mismatch :public logic_error//自定义异常类，isbn不同
{
public:
	explicit isbn_mismatch(const string &s) :
		logic_error(s){}

	isbn_mismatch(const string &s, const string &l, const string &r) :
		logic_error(s), left(l), right(r){}

	const string left, right;
};

class Sales_data;

Sales_data add(const Sales_data &sa, const Sales_data &sb);
ostream &print(ostream &os, const Sales_data &sd);
istream &read(istream &is, Sales_data &sd);


class Sales_data
{
	friend ostream& operator<<(ostream& os, const Sales_data& s_data);
	friend istream& operator>>(istream& is, Sales_data& s_data);
	friend Sales_data operator+(const Sales_data& l_data, const Sales_data& r_data);
	friend bool operator==(const Sales_data& l_data, const Sales_data& r_data);
	friend bool operator!=(const Sales_data& l_data, const Sales_data& r_data);

public:
	//构造函数
	/*Sales_data() = default;
	
	Sales_data(const string &s, unsigned u = 0, double d = 0) :
		bookNo(s), units_sold(u), revenue(u*d){}
	Sales_data(istream &is) { read(is, *this); }*/
	Sales_data(const string &s, unsigned u, double d) :
		bookNo(s), units_sold(u), revenue(u*d){
		cout << "原初构造函数" << endl;
	}
	Sales_data() :Sales_data("", 0, 0.0){ cout << "默认构造" << endl; }
	Sales_data(const string &s ) :Sales_data(s, 0, 0.0){ cout << "名字构造" << endl; }
	Sales_data(istream &is) :Sales_data("", 0, 0.0) { cout << "read构造" << endl; read(is, *this); }


	string isbn() const { return bookNo; }/*录入书编号*/
	Sales_data& combine(const Sales_data&);//类对象相加
	double avg_price() const;//返回平均单价

	//重载运算符
	
	Sales_data& operator+=(const Sales_data& s_data){ combine(s_data); return *this; }
	Sales_data& operator=(const string& s){ bookNo = s; return *this; }
	/*operator string(){ return bookNo;  }
	operator double(){ return revenue; }*/
	string bookNo;			//书编号
	unsigned units_sold = 0;//总售出册数
	double revenue = 0.0;	//总售出收入

};

ostream& operator<<(ostream& os, const Sales_data& s_data)
{
	os << s_data.isbn() << " " << s_data.units_sold << " "
		<< s_data.revenue << " " << s_data.avg_price();
	return os;
}

istream& operator>>(istream& is, Sales_data& s_data)
{
	double price;
	is >> s_data.bookNo >> s_data.units_sold >> price;
	if (is)
	{
		s_data.revenue = price*s_data.units_sold;
	}
	else
	{
		s_data = Sales_data();
	}
	return is;
}

Sales_data operator+(const Sales_data& l_data, const Sales_data& r_data)
{
	Sales_data ld = l_data;
	ld += r_data;
	return ld;
}

bool operator==(const Sales_data& l_data, const Sales_data& r_data)
{
	return l_data.bookNo == r_data.bookNo&&
		l_data.revenue == r_data.revenue&&
		l_data.units_sold == r_data.units_sold;
}
bool operator!=(const Sales_data& l_data, const Sales_data& r_data)
{
	return !(l_data == r_data);
}



Sales_data add(const Sales_data &sa, const Sales_data &sb)//类对象相加
{
	Sales_data sc;
	sc.bookNo = sa.bookNo;
	sc.revenue = sa.revenue + sb.revenue;
	sc.units_sold = sa.units_sold + sb.units_sold;
	return sc;
}

ostream &print(ostream &os, const Sales_data &sd)
{
	os << sd.bookNo     << " " 
	   << sd.units_sold << " " 
	   << sd.revenue    << " " << sd.avg_price();
	return os;
}

istream &read(istream &is, Sales_data &sd)
{
	double price = 0.0;
	is >> sd.bookNo >> sd.units_sold >> price;
	sd.revenue = sd.units_sold * price;

	return is;
}


Sales_data& Sales_data::combine(const Sales_data& sd)
{
	if (this->isbn() != sd.isbn())
		throw isbn_mismatch(string("wrong isbn"), isbn(), sd.isbn());
	this->units_sold += sd.units_sold;
	this->revenue += sd.revenue;
	return *this;
}

inline
double Sales_data::avg_price() const
{
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}

//打开命名空间
namespace std
{
	template<>//特例化版本
	struct hash<Sales_data>
	{
		typedef size_t result_type;
		typedef Sales_data argument_type;
		size_t operator()(const Sales_data& s) const;
	};
	size_t hash<Sales_data>::operator()(const Sales_data& s) const
	{
		return hash<string>()(s.bookNo) ^
			hash<unsigned>()(s.units_sold) ^
			hash<double>()(s.revenue);
	}

}

