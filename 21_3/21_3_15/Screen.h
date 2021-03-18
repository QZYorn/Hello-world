#include<string>
#include<iostream>
using namespace std;

class Screen
{
public:
	typedef string::size_type pos;

	Screen() = default;
	Screen(pos ht, pos wd) :height(ht), width(wd), contents(ht*wd, ' ') {}
	Screen(pos ht, pos wd, char c) :height(ht), width(wd), contents(ht*wd, c) {}

	char get() const { return contents[cursor]; }

	inline char get(pos ht, pos wd) const;
	Screen &move(pos r, pos c);
	Screen &set(char);
	Screen &set(pos, pos,char);
	const Screen &display(ostream &os) const{ do_display(os); return *this; }
	Screen &display(ostream &os) { do_display(os); return *this; }


private:
	void do_display(ostream &os) const { os << contents; }

	pos cursor = 0;//Êó±êÎ»ÖÃ
	pos height = 0, width = 0;//¸ß ¿í
	string contents;
	
};

inline
char Screen::get(pos ht, pos wd) const
{
	pos row = ht * width;
	return contents[row + wd];
}

inline
Screen &Screen::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

inline
Screen &Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
}

inline
Screen &Screen::set(pos row, pos col, char c)
{
	contents[row*width + col] = c;
	return *this;
}

