#include<iostream>
using namespace std;
#include<string>
#include<assert.h>


class Building;//������Buidling��

class GoodGay//�ζ���GoodGay���Լ���Ա����
{
public:
	GoodGay();//��������
	void visit();
	void visit2();
	~GoodGay();
private:
	Building *building;
};
class Building
{
	//Building��������GoodGay��ʵ������ʵ����ʱ��Ԫ��Ա��������������
	//�ʶ�GoodGay��������Building�ඨ��
friend void GoodGay::visit();//GoodGay�ĳ�Ա����visit��Building�ĺ����ѣ���Ԫ��Ա����

public:
	Building();
	string Livingroom;
	~Building();
private:
	string Bedroom;
};

Building::Building()
{
	cout << "Building���ڴ���" << endl;
	Livingroom = "����";
	Bedroom = "����";
}
Building::~Building()
{
	cout << "Building��������" << endl;
}



GoodGay::GoodGay()//����ʵ��
{
	cout << "1" << endl;
	building = new Building;//��ʱBuilding����
	cout << "GoodGay���ڴ���" << endl;

}
void GoodGay::visit()
{
	cout << "visit���ڷ���" << building->Livingroom << endl;
	cout << "visit���ڷ���" << building->Bedroom << endl;
}
void GoodGay::visit2()
{
	cout << "visit2���ڷ���" << building->Livingroom << endl;
	//cout << "visit2���ڷ���" << building->Bedroom << endl;

}

GoodGay::~GoodGay()
{
	//cout << "GoodGay��������" << endl;
	cout << "1" << endl;
	assert(building != NULL);
	cout << "2" << endl;
	delete building;//��ʱBuidling����
	cout << "3" << endl;
	building = NULL;
	cout << "GoodGay��������" << endl;
}

void Test01()
{
	GoodGay g1;
	g1.visit();
}

int main()
{
	Test01();
	return 0;
}