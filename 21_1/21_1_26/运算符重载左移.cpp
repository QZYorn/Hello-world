#include<iostream>
using namespace std;

class Person
{
	friend ostream& operator<<(ostream &out, Person &p);//��Ԫȫ�ֺ���
public:
	Person(int a, int b)
	{
		m_a = a;
		m_b = b;
	}
	
private:
	int m_a;
	int m_b;
};

//ȫ�ֺ���ʵ���������������
//����Զ�����������
ostream& operator<<(ostream &out, Person &p)//operate<<(cout, p) �ȼ�  cout << p
{
	out << "m_a = " << p.m_a << "    m_b = " << p.m_b;//��ʽ���˼��
	return out;
}

void Test01()
{
	Person p1(10,10);
	/*p1.m_a = 10;
	p1.m_b = 10;*/
	cout << p1 <<"   jiejiejie" << endl;
	cout << "jiejiejie   " << p1 << endl;

}

int main()
{
	Test01();
	return 0;
}