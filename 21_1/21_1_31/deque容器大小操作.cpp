#include<iostream>
using namespace std;
#include<deque>

void printDeque(const deque<int> &d)
{
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		//*it = 100;
		cout << *it << " ";
	}
	cout << endl;
}

void Test01()
{
	deque<int> d1;
	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
	}

	if (d1.empty())
	{
		cout << "Ϊ��" << endl;
	}
	else
	{
		cout << "��СΪ��" << d1.size() << endl;
		printDeque(d1);
	}

	d1.resize(20);//Ĭ�ϲ�ȫ0
	printDeque(d1);
	d1.resize(25, 100);//��100��ȫ
	printDeque(d1);
	d1.resize(3);//ֻ��������Ԫ�أ�����ɾ��
	printDeque(d1);
}



int main()
{
	Test01();
	system("pause");
	return 0;
}