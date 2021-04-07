#include<string>
#include<iostream>
using namespace std;

class Sales_data;

Sales_data add(const Sales_data &sa, const Sales_data &sb);
ostream &print(ostream &os, const Sales_data &sd);
istream &read(istream &is, Sales_data &sd);

class Sales_data
{
public:
	//���캯��
	/*Sales_data() = default;
	
	Sales_data(const string &s, unsigned u = 0, double d = 0) :
		bookNo(s), units_sold(u), revenue(u*d){}
	Sales_data(istream &is) { read(is, *this); }*/
	Sales_data(const string &s, unsigned u, double d) :
		bookNo(s), units_sold(u), revenue(u*d){
		cout << "ԭ�����캯��" << endl;
	}
	Sales_data() :Sales_data("", 0, 0.0){ cout << "Ĭ�Ϲ���" << endl; }
	Sales_data(const string &s ) :Sales_data(s, 0, 0.0){ cout << "���ֹ���" << endl; }
	Sales_data(istream &is) :Sales_data("", 0, 0.0) { cout << "read����" << endl; read(is, *this); }


	string isbn() const { return bookNo; }/*¼������*/
	Sales_data& combine(const Sales_data&);//��������
	double avg_price() const;//����ƽ������

	string bookNo;			//����
	unsigned units_sold = 0;//���۳�����
	double revenue = 0.0;	//���۳�����

};

Sales_data add(const Sales_data &sa, const Sales_data &sb)//��������
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