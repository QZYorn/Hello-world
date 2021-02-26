#include<iostream>
#include"List.hpp"
#include<time.h>
using namespace std;

void visitDouble(int &i)
{
	i *= 2;
}

template<class T>
class visitAdd20
{
public:
	virtual void operator()(T &e)
	{
		e += 20;
	}
};


void Test01()
{
	List<int> li1;//默认构造
	for (int i = 0; i < 10; i++)
	{
		li1.insertAsLast(i);
	}
	List<int> li2(li1);//整体 拷贝构造
	List<int> li3(li2.first(), li2.size()-1);//区间拷贝构造，前9个
	List<int> li4(li3, 1, li3.size()-1);//区间拷贝构造，跳过第一个
	
	Posi(int) p1 = li1.first();
	Posi(int) p2 = li2.first(); 
	Posi(int) p3 = li3.first();
	Posi(int) p4 = li4.first();


	//li1
	cout << "li1: ";
	for (int i = 0; i < li1.size(); i++)
	{
		cout << p1->data << " ";
		p1 = p1->succ;
	}
	cout << endl;


	//li2
	for (int i = 0; i < 10; i++)
	{
		Posi(int) p = li2.find(i);
		if (p != NULL)
		li2.insertAsSucc(p, p->data);
	}
	cout << "li2: ";
	//int count = li2.deduplicate();//去重
	int count = li2.uniquify();//去重
	if (0 < count)
	{
		cout << "删除重复的" << count << "个元素后： ";
	}
	p2 = li2.first();//重定位首元素
	for (int i = 0; i < li2.size(); i++)
	{
		cout << p2->data << " ";
		p2 = p2->succ;
	}
	cout << endl;


	//li3
	cout << "li3: ";
	for (int i = 0; i < 10; i++)
	{
		li3.insertAsFirst(i);
	}

	li3.sort();
	li3.traverse(visitDouble);//遍历加倍
	p3 = li3.first();
	for (int i = 0; i < li3.size(); i++)
	{
		cout << p3->data << " ";
		p3 = p3->succ;
	}
	cout << endl;


	//li4
	cout << "li4: "; 
	li4.traverse(visitAdd20<int>());//遍历+20
	for (int i = 0; i < li4.size(); i++)
	{
		cout << p4->data << " ";
		p4 = p4->succ;
	}
	cout << endl;


}

int main()
{
	srand((unsigned int)time(NULL));
	Test01();
	system("pause");
	return 0;
}