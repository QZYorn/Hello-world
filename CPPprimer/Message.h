#pragma once

#include<iostream>
#include<string>
#include<set>
using namespace std;



class Message;
class Floder
{
public:
	void addMsg(Message* mp);
	void remMsg(Message* mp);
private:
	set<Message*> message;
};

class Message
{
	friend class Floder;
public:
	Message(string value = " ") :contents(value){}
	Message(const Message& m);
	Message(Message&& m);

	~Message(){ remove_from_Floder(); }

	Message& operator=(Message&& m);
	Message& operator=(const Message& m);
	void save(Floder& f);
	void remove(Floder& f);
	void addFld(Floder *fp);
	void remFld(Floder *fp);

private:
	string contents;
	set<Floder*> floder;

	void add_to_Floder(const Message& m);//�����󣬱�messageӦ���� Ŀ��message���ڵ�ÿ��floder��
	void remove_from_Floder();//�ӱ�message���ڵ�ÿ��floder��ɾȥ��message
	void move_Floder(Message *m);
};

Message::Message(const Message& m) :
contents(m.contents), floder(m.floder)
{
	//������Ϊ������������ģ���Դ������ԴĿ¼��ԴĿ¼��Ӧ���뱾����
	add_to_Floder(m);
}

Message::Message(Message&& m) :
contents(move(m.contents))
{
	move_Floder(&m);
}

Message& Message::operator=(Message&& m)
{
	remove_from_Floder();
	contents = move(m.contents);
	move_Floder(&m);
	return *this;
}

Message& Message::operator=(const Message& m)
{
	remove_from_Floder();//����������Ŀ¼��ɾȥ�������ַ
	this->contents = m.contents;
	this->floder = m.floder;
	add_to_Floder(m);
	return *this;
}

void Message::save(Floder& f)
{
	floder.insert(&f);//����������Ŀ¼����
	f.addMsg(this);//Ŀ¼����ӵ�������ĵ�ַ
}

void Message::remove(Floder& f)
{
	floder.erase(&f);
	f.remMsg(this);
}

void Message::addFld(Floder *fp)
{
	floder.insert(fp);
	fp->addMsg(this);
}
void Message::remFld(Floder *fp)
{
	floder.erase(fp);
	fp->remMsg(this);
}

void Message::add_to_Floder(const Message& m)
{
	for (auto f : m.floder)
	{
		f->addMsg(this);
	}
}
void Message::remove_from_Floder()
{
	for (auto f : this->floder)
	{
		f->remMsg(this);
	}
}

void Message::move_Floder(Message *m)
{
	floder = move(m->floder);
	for (auto f : floder)
	{
		f->remMsg(m);
		f->addMsg(this);
	}
	m->floder.clear();
}


void Floder::addMsg(Message* mp)
{
	message.insert(mp);
}
void Floder::remMsg(Message* mp)
{
	message.erase(mp);
}