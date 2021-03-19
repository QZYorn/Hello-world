#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

istream &read(istream &is)
{
	char c;
	while (!is.eof() && is >> c)
	{
		cout << c;
	}
	is.clear();
	return is;
}

void printVector()
{
	ifstream ifs("test.txt");
	vector<string> vs;
	/*if (ifs.is_open())
	{
		string s;
		while (getline(ifs,s))
		{
			vs.push_back(s);
		}
	}
	else
	{
		cerr << "get wrong file" << endl;
	}*/

	if (ifs.is_open())
	{
		string s;
		while (!ifs.eof() && ifs >> s)
		{
			vs.push_back(s);
		}
	}
	else
	{
		cerr << "get wrong file" << endl;
	}
	ifs.close();

}

struct PersonInfo
{
	string name;
	vector<string> phones;
};

void test8_1_2()
{

	//8.2
	read(cin);

	printVector();

	//8.9

	string s("abcde");
	istringstream iss(s);
	read(iss);

	//8.11
	string line, word;
	vector<PersonInfo> people;
	istringstream record(line);
	while (getline(cin, line))
	{
		PersonInfo info;
		record.str(line);
		record >> info.name;
		while (record >> word)
		{
			info.phones.push_back(word);
		}
		people.push_back(info);
	}

}

int main()
{
	test8_1_2();
	return 0;
}