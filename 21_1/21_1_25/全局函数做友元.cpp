#include<iostream>
using namespace std;
#include<string>

class Room
{
	friend void GoodGay(Room &r);//ȫ�ֺ�������Ԫ
public:
	Room()
	{
		Livingroom = "����";
		Bedroom = "����";
		cout << "begin" << endl;
	}
	~Room()
	{
		
		cout << "end" << endl;
	}


	string Livingroom;
private:
	string Bedroom;

};
void GoodGay(Room &r)
{
	cout << "�û������ڷ���> > > " << r.Livingroom << endl;
	cout << "�û������ڷ���> > > " << r.Bedroom << endl;//����˽�г�Ա����

}

void Test01()
{
	Room r;
	GoodGay(r);
}

int main()
{
	Test01();
	return 0;
}