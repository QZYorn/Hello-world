#pragma once

#include<iostream>
#include<string>
#include<set>
#include<memory>
using namespace std;


class Quote
{
public:
	Quote() = default;
	Quote(const string& book, double sales_price) :
		bookNo(book), price(sales_price){}
	//拷贝控制函数
	Quote(const Quote& q) :bookNo(q.bookNo), price(q.price){}//拷贝构造
	Quote(Quote&& q) :bookNo(move(q.bookNo)), price(q.price){}//移动构造
	Quote& operator=(const Quote& q){ bookNo = q.bookNo; price = q.price; return *this; }//拷贝赋值
	Quote& operator=(Quote&& q){ bookNo = move(q.bookNo); price = q.price; return *this; }//移动赋值

	string isbn()const{ return bookNo; }
	Quote* clone(){ return new Quote(*this); }
	Quote* clone() const{ return new Quote(move(*this)); }


	virtual double net_price(size_t n) const//返回销售总额
	{
		return n * price;
	}
	virtual void debug() const//显示数据成员
	{
		cout << " bookNo: " << bookNo << " price: " << price;
	}
	virtual ~Quote() = default;

private:
	string bookNo;//书籍的ISBN编号
protected:
	double price = 0.0;//书籍不打折情况下的价格
};




class Disc_Quote :public Quote
{
public:
	Disc_Quote() = default;
	Disc_Quote(const string &book, double price, size_t qty, double disc) :
		Quote(book,price),quantity(qty),discount(disc) {}
	//拷贝控制
	Disc_Quote(const Disc_Quote& q) :Quote(q),quantity(q.quantity),discount(q.discount){}//拷贝构造
	Disc_Quote(Disc_Quote&& q) :Quote(move(q)), quantity(q.quantity), discount(q.discount){}//移动构造
	Disc_Quote& operator=(const Disc_Quote& q){ 
		Quote::operator=(q); 
		quantity = q.quantity; 
		discount = q.discount; 
		return *this; }//拷贝赋值
	Disc_Quote& operator=(Disc_Quote&& q){
		Quote::operator=(move(q)); 
		quantity = q.quantity; 
		discount = q.discount; 
		return *this;}//移动赋值

	

	double net_price(size_t n) const = 0;
protected:
	size_t quantity = 0;//折扣适用的购买量
	double discount = 0.0;//表示折扣的小数值
};







class Bulk_quote :public Disc_Quote
{
public:
	using Disc_Quote::Disc_Quote;
	Bulk_quote() = default;
	Bulk_quote(const string &book, double p, size_t qty, double disc) :
		Disc_Quote(book, p,qty,disc){}
	//拷贝控制
	Bulk_quote(const Bulk_quote& q) :Disc_Quote(q){}//拷贝构造
	Bulk_quote(Bulk_quote&& q) :Disc_Quote(move(q)){}//移动构造
	Bulk_quote& operator=(const Bulk_quote& q){ Disc_Quote::operator=(q); return *this; }//拷贝赋值
	Bulk_quote& operator=(Bulk_quote&& q){ Disc_Quote::operator=(move(q)); return *this; }//移动赋值

	Bulk_quote* clone(){ return new Bulk_quote(*this); }
	Bulk_quote* clone() const{ return new Bulk_quote(move(*this)); }

	double net_price(size_t n) const override;
	void debug() const override;
private:
};

double Bulk_quote::net_price(size_t n) const
{
	if (n <= quantity)
		return n * price;
	else
		return n * price * (1 - discount);
}
void Bulk_quote::debug() const
{
	Quote::debug();
	cout << " min_qty: " << quantity << " discount: " << discount;
}







class Limi_quote :public Disc_Quote
{
public:
	Limi_quote() = default;
	Limi_quote(const string &book, double p, size_t qty, double disc) :
		Disc_Quote(book, p, qty, disc){}
	double net_price(size_t n) const override;
	void debug() const override;
};

double Limi_quote::net_price(size_t n) const
{
	if (n <= quantity)
		return n * price * (1 - discount);
	else
		return (n - quantity) * price + quantity * price * (1 - discount);
}

void Limi_quote::debug() const
{
	Quote::debug();
	cout << " min_qty: " << quantity << " discount: " << discount;
}


double print_total(ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << " ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}




class Basket
{
public:
	//增加一本新书进入购物篮，
	void add_item(const Quote &sale)
	{
		item.insert(shared_ptr<Quote>(sale.clone()));
	}
	void add_item(Quote &&sale)
	{
		item.insert(shared_ptr<Quote>(move(sale).clone()));
	}
	//打印每本书的总价和购物篮中所有书的总价
	double total_receipt(ostream& os) const
	{
		double sum = 0.0;
		for (auto it = item.begin(); it != item.end(); it = item.upper_bound(*it))
		{
			sum += print_total(os, **it, item.count(*it));
		}
		os << "Total Sale:" << sum << endl;
		return sum;
	}

	static bool compare(const shared_ptr<Quote> &lhs, const shared_ptr<Quote> &rhs)
	{
		return lhs->isbn() < rhs->isbn();
	}
private:
	//保存多个书籍报价，相同ISBN书籍存放在相邻位置
	multiset<shared_ptr<Quote>, decltype(compare)*> item{ compare };
};
