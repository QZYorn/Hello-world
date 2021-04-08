#pragma once

#include<iostream>
#include<string>
using namespace std;


class Quote
{
public:
	Quote() = default;
	Quote(const string& book, double sales_price) :
		bookNo(book), price(sales_price){}
	string isbn()const{ return bookNo; }

	virtual double net_price(size_t n) const//���������ܶ�
	{
		return n * price;
	}
	virtual void debug() const//��ʾ���ݳ�Ա
	{
		cout << " bookNo: " << bookNo << " price: " << price;
	}
	virtual ~Quote() = default;

private:
	string bookNo;//�鼮��ISBN���
protected:
	double price = 0.0;//�鼮����������µļ۸�
};



class Bulk_quote :public Quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const string &book, double p, size_t qty, double disc) :
		Quote(book, p), min_qty(qty), discount(disc){}
	double net_price(size_t n) const override;
	void debug() const override;
private:
	size_t min_qty = 0;//�ﵽ�ۿ۵���С������
	double discount = 0.0;//�ۿ۶�
};

double Bulk_quote::net_price(size_t n) const
{
	if (n <= min_qty)
		return n * price;
	else
		return n * price * (1 - discount);
}
void Bulk_quote::debug() const
{
	Quote::debug();
	cout << " min_qty: " << min_qty << " discount: " << discount;
}




class Limi_quote :public Quote
{
public:
	Limi_quote() = default;
	Limi_quote(const string &book, double p, size_t qty, double disc) :
		Quote(book, p), min_qty(qty), discount(disc){}
	double net_price(size_t n) const override;
	void debug() const override;
private:
	size_t min_qty = 0;//�����ۿ۵���С������
	double discount = 0.0;//�ۿ۶�
};
double Limi_quote::net_price(size_t n) const
{
	if (n <= min_qty)
		return n * price * (1 - discount);
	else
		return (n - min_qty) * price + min_qty * price * (1 - discount);
}
void Limi_quote::debug() const
{
	Quote::debug();
	cout << " min_qty: " << min_qty << " discount: " << discount;
}


double print_total(ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << " ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}


