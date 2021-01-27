#include<iostream>
using namespace std;

class Drink//饮品抽象类
{
public:
	//煮水
	virtual void Boil() = 0;

	//冲泡
	virtual void Brew() = 0;

	//倒出
	virtual void PowlOut() = 0;

	//加料
	virtual void PutIn() = 0;

	void MakeDrink()
	{
		cout << "制作中..." << endl;
		Boil();
		Brew();
		PowlOut();
		PutIn();
		cout << "制作完成！！" << endl;
	}
};

class Coffee :public Drink//咖啡子类
{
public:
	//煮水
	virtual void Boil()
	{
		cout << "使用上等的牛奶" << endl;
	}

	//冲泡
	virtual void Brew()
	{
		cout << "加入咖啡基底" << endl;
	}

	//倒出
	virtual void PowlOut()
	{
		cout << "倒入马克杯中"<< endl;
	}

	//加料
	virtual void PutIn()
	{
		cout << "加入适量白糖和奶球" << endl;
	}
};

class Cup:public Drink//茶子类
{
public:
	//煮水
	virtual void Boil()
	{
		cout << "使用高山间流水" << endl;
	}

	//冲泡
	virtual void Brew()
	{
		cout << "加入乌龙茶叶" << endl;
	}

	//倒出
	virtual void PowlOut()
	{
		cout << "倒入茶杯中" << endl;
	}

	//加料
	virtual void PutIn()
	{
		cout << "加入适量枸杞" << endl;
	}
};

void doWork(Drink* d)//等价 Drink* d = new xxxxx
{
	d->MakeDrink();
	delete d;//释放
}

void Test01()
{
	doWork(new Coffee);//堆区开辟内存，并传入子类对象指针
	cout << "-------------" << endl;
	doWork(new Cup);
}

int main()
{
	Test01();
	return 0;
}