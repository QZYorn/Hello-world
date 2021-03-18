#include<string>
#include<iostream>
using namespace std;

class Person
{
	string _name;
	string _address;

public:
	Person(const string &n, const string &a) :_name(n), _address(a){}

	string name() const
	{
		return _name;
	}

	string address() const
	{
		return _address;
	}

	ostream &print(ostream&, const Person&);
	istream &read(istream&, Person&);
};

ostream &Person::print(ostream &os, const Person &pe)
{
	os << pe.name() << " " << pe.address();
	return os;
}

istream &Person::read(istream &is, Person &pe)
{
	is >> pe._name >> pe._address;
	return is;
}
