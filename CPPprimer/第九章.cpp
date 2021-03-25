#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
//#include<iterator>
#include<sstream>
#include<vector>
#include<list>
#include<deque>
#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
using namespace std;
using namespace std::placeholders;

void test9_5_1()
{
	cout << "\n9.5.1" << endl;
	//9.41
	vector<char> cvec{ 'a','b','c','e','d'};
	string s(cvec.begin(), cvec.end());

	//9.42
	s.reserve(100);
}

void singleStr(string &s, const string &oldVal, const string &newVal)
{
	auto iter = s.begin();
	auto len = oldVal.size();
	while (iter < s.end() - len + 1)
	{
		if (string(iter, iter+len) == oldVal)
		{
			iter = s.erase(iter, iter + len);
			iter = s.insert(iter, newVal.begin(), newVal.end());
			iter += newVal.size();
		}
		else
		{
			++iter;
		}
	}
}

void singleStr2(string &s, const string &oldVal, const string &newVal)
{
	int pos = 0;
	int len = oldVal.size();
	while (pos+len <= s.size())
	{
		string tmpS = s.substr(pos, len);
		if (tmpS == oldVal)
		{
			s.replace(pos, len, newVal);
			pos += newVal.size();
		}
		else
		{
			++pos;
		}
	}
}

string changeName(string s, const string &pre, const string &pos)
{
	s.insert(s.begin(), pre.begin(), pre.end());
	s.append(pos.begin(),pos.end());
	return s;
}

string changeName2(string s, const string &pre, const string &pos)
{
	s.insert(0, pre, 0, pre.size());
	s.insert(s.size(), pos, 0, pos.size());
	return s;
}
void test9_5_2()
{
	cout << "\n9.5.2" << endl;

	//9.43
	string s{ "in the bigger in the home" };
	singleStr(s, "bigger", "big");
	cout << s << endl;

	//9.44
	singleStr2(s, "in the", "in");
	cout << s << endl;

	//9.45
	string name{ "Yorn" };
	cout << changeName(name, "QZ.", ".dead") << endl;

	//9.46
	cout << changeName2(name, "QZ.", ".dead") << endl;
}

void test9_5_3()
{
	cout << "\n9.5.2" << endl;

	//9.47
	string s{ "ab2c3d7R4E6" };
	string digS{ "0123456789" };
	string letS{ "abcdRE" };
	int pos = 0;
	//1.
	while ((pos = s.find_first_of(digS,pos)) != string::npos)
	{
		cout << s[pos] << " ";
		++pos;
	}
	cout << endl;

	pos = 0;
	while ((pos = s.find_first_of(letS, pos)) != string::npos)
	{
		cout << s[pos] << " ";
		++pos;
	}
	cout << endl;

	//2.
	pos = 0;
	while ((pos = s.find_first_not_of(letS, pos)) != string::npos)
	{
		cout << s[pos] << " ";
		++pos;
	}
	cout << endl;

	pos = 0;
	while ((pos = s.find_first_not_of(digS, pos)) != string::npos)
	{
		cout << s[pos] << " ";
		++pos;
	}
	cout << endl;

	//9.48
	cout << (s.find(digS, 0) == string::npos) << endl;


}

void test9_5_5()
{
	cout << "\n9.5.5" << endl;

	//9.50
	vector<string> svec{ "5", "15", "2", "3", "4" };
	int isum = 0;
	auto iter = svec.begin();
	while (iter != svec.end())
	{
		isum += stoi(*iter);
		++iter;
	}
	cout << "isum = " << isum << endl;

	vector<string> svec2{ "2.5", "3.6", "1.2", "1.1" };
	double dsum = 0;
	auto iter2 = svec2.begin();
	while (iter2 != svec2.end())
	{
		dsum += stod(*iter2);
		++iter2;
	}
	cout << "dsum = " << dsum << endl;

	
}

int main()
{
	test9_5_1();
	test9_5_2();
	test9_5_3();
	test9_5_5();
	return 0;
}