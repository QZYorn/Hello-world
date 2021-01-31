#include<iostream>
using namespace std;
#include<deque>
#include<string>
#include<vector>
#include<algorithm>
#include<time.h>
#include<Windows.h>

class Person
{
public:
	Person(string name, int score)
	{
		m_Name = name;
		m_Score = score;
	}


	string m_Name;
	int m_Score;
};

void creatPerson(vector<Person> &v)
{
	string num = "ABCDE";
	for (int i = 0; i < 5; i++)
	{
		
		string name = "ѡ��";
		name += num[i];
		Person p(name, 0);
		v.push_back(p);
	}
}

void printPerson(vector<Person> &v)
{
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "���֣�" << it->m_Name << "  �ɼ���" << it->m_Score << endl;
	}
}

void setScore(vector<Person> &v)
{
	for (int i = 0; i < v.size(); i++)
	{
		deque<int> d;
		//���ʮ��
		for (int j = 0; j < 10; j++)
		{
			int score = rand() % 41 + 60;
			d.push_back(score);
		}
		//����
		sort(d.begin(), d.end());

		d.pop_front();//ȥ��һ����߷�
		d.pop_back();//ȥ��һ����ͷ�

		//�ܷ�
		int  sum = 0;
		for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
		{
			sum += *dit;
		}

		//����ƽ����
		v[i].m_Score = sum / d.size();
	}
}

void Test01()
{
	srand((unsigned int)time(NULL));

	vector<Person> v;
	//��������ѡ��
	creatPerson(v);
	//�������ƽ����
	setScore(v);
	//������ӡ
	printPerson(v);
}



int main()
{
	Test01();
	system("pause");
	return 0;
}