#include<iostream>
using namespace std;
#include<string>
#include<assert.h>

class Building
{
	friend class GoodGay;//GoodGay��Building�ĺ����ѣ����Է���Building��˽�г�Ա
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

class GoodGay
{
public:
	GoodGay();//��������
	void visit();
	~GoodGay();
private:
	Building *building;
};

GoodGay::GoodGay()//����ʵ��
{
	cout << "1" << endl;
	building = new Building;//��ʱBuilding����
	cout << "GoodGay���ڴ���" << endl;
}
void GoodGay::visit()
{
	cout << "���ڷ���" << building->Livingroom << endl;
	cout << "���ڷ���" << building->Bedroom << endl;
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