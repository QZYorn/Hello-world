#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<numeric>

void MyPrint(int a)
{
	cout << a << " ";
}



void test01()
{
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 5);
	}

	vector<int> vTarget;
	//��ǰԤ���ռ䣬����Ϊ��С���ϵĴ�С
	vTarget.resize(min(v1.size(), v2.size()));
	
	//��Դ���Ͼ�Ϊ��������
	//����Ŀ���������һ��Ԫ�صĵ�����
	vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());
	
	//������ǰ�����ˣ�����ֻ����������һ������Ԫ�ؼ��ɣ����ر������������һ��λ��
	for_each(vTarget.begin(), itEnd, MyPrint);
}

int main()
{
	test01();
	system("pause");
	return 0;
}