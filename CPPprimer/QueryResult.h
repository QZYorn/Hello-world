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

//#define DEBUG

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
					line.reset(new (set<line_no>));
				}
				line->insert(curr);
			}
			++curr;
		}
	}

	QueryResult query(const string& s) const;

private:
	//���д洢�ı����ݵ�vector����
	shared_ptr<vector<string>> file;
	//����������кż���set�İ�  <���ʣ�set<�����к�>>
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
	shared_ptr<set<line_no>> get_line()
	{
		return line;
	}
	shared_ptr<vector<string>> get_file()
	{
		return file;
	}
private:
	//��ѯ����
	string word;
	//ȫ���ı�
	shared_ptr<vector<string>> file;
	//���ʳ����кż���
	shared_ptr<set<line_no>> line;

};

//����{����s��ȫ���ı�������s���ֵ��кż���set}
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





class Query;
class Query_base
{
	friend class Query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	//evalʹ�ø���TextQuery�����뵱ǰQueryƥ��Ĳ�ѯ�����ɲ�ѯ���QueryResult������
	virtual QueryResult eval(const TextQuery &tq)const = 0;
	//rep��ʾ��ѯ��һ��string
	virtual string rep()const = 0;
};

class WordQuery :public Query_base
{
	friend class Query;
	WordQuery(const string &s) :query_word(s)
	{	
#ifdef DEBUG
		cout << " WordQuery " << endl;
#endif
	}

	QueryResult eval(const TextQuery& tq)const
	{
		return tq.query(query_word);
	}
	string rep()const
	{
#ifdef DEBUG 
		cout << "WordQuery:rep()" << endl;
#endif
		return query_word;
	}

	string query_word;//Ҫ���ҵĵ���
};



class Query
{
	friend Query operator~(const Query &q);
	friend Query operator&(const Query &lq, const Query &rq);
	friend Query operator|(const Query &lq, const Query &rq);
public:
	Query(const string &s) :q(new WordQuery(s)){}
	QueryResult eval(const TextQuery& tq)const{ return q->eval(tq); }

	string rep() const
	{
#ifdef DEBUG 
		cout << "Query:rep()" << endl;
#endif
		return q->rep();
	}


private:
	Query(const shared_ptr<Query_base> base) :q(base)
	{
#ifdef DEBUG
		cout << " Query " << endl;
#endif
	}

	shared_ptr<Query_base> q;

};





class NotQuery :public Query_base
{
	friend Query operator~(const Query &q);

	NotQuery(const Query&q) :query(q)
	{
#ifdef DEBUG
			cout << " NotQuery " << endl;
#endif
	}
	

	QueryResult eval(const TextQuery& tq)const
	{
		auto result = query.eval(tq);
		auto ret_line = make_shared<set<line_no>>();
		auto beg = result.get_line()->begin();
		auto end = result.get_line()->end();
		auto sz = result.get_file()->size();
		for(size_t n = 0;n < sz;++n)
		{
			if (beg == end || *beg != n)
			{
				ret_line->insert(n);
			}
			else if (beg != end)
			{
				++beg;
			}
		}
		return QueryResult(rep(), result.get_file(), ret_line);
	}

	string rep()const
	{
#ifdef DEBUG 
		cout << "NotQuery:rep()" << endl;
#endif
		return "~(" + query.rep() + ")"; 
	}//~(s)

	Query query;
};

class BinQuery :public Query_base
{
protected:
	BinQuery(const Query &lq, const Query &rq, string s)
			:lhs(lq), rhs(rq), opSym(s)
	{
#ifdef DEBUG
		cout << " BinQuery " << endl;
#endif
	}

	//�����࣬�̳е�������eval()
	string rep()const
	{ 
#ifdef DEBUG 
		cout << "BinQuery:rep()" << endl;
#endif
	return "(" + lhs.rep() +
	       " " + opSym     + 
	       " " + rhs.rep() + ")"; 
	}

	Query lhs, rhs;//���Ҳ��������
	string opSym;//���������
};

class AndQuery :public BinQuery
{
	friend Query operator&(const Query &lq, const Query &rq);
	AndQuery(const Query &l, const Query &r) :BinQuery(l, r, "&")
	{
#ifdef DEBUG
		cout << " AndQuery " << endl;
#endif
	}

	QueryResult eval(const TextQuery &tq)const
	{
		auto left = lhs.eval(tq), right = rhs.eval(tq);
		auto ret_line = make_shared<set<line_no>>(left.get_line()->begin(), left.get_line()->end());
		set_intersection(left.get_line()->begin(), left.get_line()->end(),
			right.get_line()->begin(), right.get_line()->end(),
			inserter(*ret_line, ret_line->begin()));
		return QueryResult(rep(), left.get_file(), ret_line);
	}
};

class OrQuery :public BinQuery
{
	friend Query operator|(const Query &lq, const Query &rq);
	OrQuery(const Query &l, const Query &r) :BinQuery(l, r, "|")
	{
#ifdef DEBUG
		cout << " OrQuery " << endl;
#endif
	}

	QueryResult eval(const TextQuery &tq)const
	{
		auto left = lhs.eval(tq), right = rhs.eval(tq);
		auto ret_line = make_shared<set<line_no>>(left.get_line()->begin(),left.get_line()->end());
		ret_line->insert(right.get_line()->begin(), right.get_line()->end());
		return QueryResult(rep(), left.get_file(), ret_line);
	}
};







//������������
ostream& operator<<(ostream &os, const Query& q)
{
	//repΪ�����
	return os << q.rep();
}

//����λ�������
inline
Query operator~(const Query &q)
{
	return shared_ptr<Query_base>(new NotQuery(q));
}

//����λ�������
inline
Query operator&(const Query &lq, const Query &rq)
{
	return shared_ptr<Query_base>(new AndQuery(lq, rq));
}

//����λ�������
inline
Query operator|(const Query &lq, const Query &rq)
{
	return shared_ptr<Query_base>(new OrQuery(lq, rq));
}