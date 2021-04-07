#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<fstream>
#include<set>
#include<map>
#include<sstream>
using namespace std;



class QueryResult;
class TextQuery
{
public:
	typedef size_t line_no;
	TextQuery(ifstream &ifs) :file(new vector<string>)
	{
		string s;
		int curr = 0;
		while (getline(ifs, s))
		{
			file->push_back(s);
			string word;
			istringstream iss(s);
			while (iss >> word)
			{
				auto &line = word_line[word];
				if (!line)
				{
					line.reset(make_shared<set<line_no>>);
				}
				line->insert(curr);
			}
			++curr;
		}
	}

	QueryResult query(const string& s) const;

private:

	shared_ptr<vector<string>> file;
	map<string, shared_ptr<set<line_no>>> word_line;
};

class QueryResult
{
	friend ostream& print(ostream& os, QueryResult& qr);

	typedef size_t line_no;
public:
	QueryResult(string s,
		shared_ptr<vector<string>> p,
		shared_ptr<set<line_no>> l)
		:word(s), file(p), line(l){}
private:
	string word;
	shared_ptr<vector<string>> file;
	shared_ptr<set<line_no>> line;

};

QueryResult TextQuery::query(const string& s) const
{
	auto line = word_line.find(s);
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	if (line == word_line.end())
	{
		return{ s, file, nodata };
	}
	return{ s, file, line->second };
}
