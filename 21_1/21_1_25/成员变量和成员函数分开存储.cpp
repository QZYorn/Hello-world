#include<iostream>
using namespace std;

class Person
{
	int m_a;		//�Ǿ�̬��Ա���� ռ�����С�ռ�
	static int m_b; //��̬��Ա����	 �����������
	void func(){}   //�Ǿ�̬��Ա���� �����������
	static void func1(){}//��̬��Ա���� �����������
};
int Person::m_b = 100;


void Test01()
{
	Person p;
	cout << "sizeofΪ" << sizeof(p) << endl;//�ն����СΪ1
	cout << "sizeofΪ" << sizeof(Person) << endl;//�����СΪ1
}

void Test02()
{
	Person p;
	cout << "sizeofΪ" << sizeof(p) << endl;

}

int main()
{
	//Test01();
	Test02();
	return 0;
}