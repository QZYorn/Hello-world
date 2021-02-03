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
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	
	int count = accumulate(v1.begin(), v1.end(), 0);
	cout << "ÀÛ¼ÓÖµÎª£º" << count << endl;
}

int main()
{
	test01();
	system("pause");
	return 0;
}