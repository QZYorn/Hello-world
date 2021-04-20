#include<string>
#include<iostream>
using namespace std;

class Token
{
private:
	enum TOK{ INT, CHAR, DBL}tok;//创建匿名枚举类型并定义一个tok对象，判别式
	union
	{
		int ival;
		char cval;
		double dval;
	};
	void copyUnion(const Token& t);
	void copyUnion(Token&& t);
public:
	Token() :tok(INT), ival(0){}
	Token(const Token &t) :tok(t.get_tok()){ copyUnion(t); }
	Token(Token &&t) :tok(move(t.get_tok())){ copyUnion(move(t)); }
	Token &operator=(const Token &t){ copyUnion(t); return *this; }
	~Token(){}

	Token &operator=(int i)   { ival = i; return *this; }
	Token &operator=(char c)  { cval = c; return *this; }
	Token &operator=(double d){ dval = d; return *this; }

	TOK get_tok()const{ return tok; }

};

void Token::copyUnion(const Token& t)
{
	switch (t.get_tok())
	{
	case Token::INT:  ival = t.ival; break;
	case Token::CHAR: cval = t.cval; break;
	case Token::DBL:  dval = t.dval; break;
	}
}
void Token::copyUnion(Token&& t)
{
	switch (t.get_tok())
	{
	case Token::INT:  ival = move(t.ival); break;
	case Token::CHAR: cval = move(t.cval); break;
	case Token::DBL:  dval = move(t.dval); break;
	}
}
