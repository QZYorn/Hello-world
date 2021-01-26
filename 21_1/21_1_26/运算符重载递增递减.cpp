#include<iostream>
using namespace std;

class Person
{
	friend ostream& operator<<(ostream &out, Person &p);
public:
	Person()
	{
		m_a = 0;
	}

	Person& operator++()//����ǰ�����������
	{
		m_a++;//��++
		return *this;//�ٷ���
	}
	Person operator++(int)//�����������������
	{
		Person tmp = *this;//�ȼ�¼
		m_a++;//��++
		return tmp;//���ؼ�¼ֵ����++ǰ
	}
	Person& operator--()//�ݼ�ǰ�����������
	{
		m_a--;
		return *this;
	}
	Person operator--(int)//�����������������
	{
		Person tmp = *this;
		m_a--;
		return tmp;
	}

private:
	int m_a;
};

//<<���������
ostream& operator<<(ostream &out, Person &p)
{
	out << "m_a = " << p.m_a;
	return out;
}

void Test01()
{
	Person p1;
	cout << ++(++p1) << endl;
	cout << p1 << endl;
	cout << p1++ << endl;
	cout << p1 << endl;
	cout << --(--p1) << endl;
	cout << p1 << endl;
	cout << p1-- << endl;
	cout << p1 << endl;

}
int main()
{
	Test01();
	return 0;
}