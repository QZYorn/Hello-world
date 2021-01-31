#include<iostream>
using namespace std;
#include<vector>

void vprint(vector<int> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void Test01()
{
	vector<int> v1;

	//尾插
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	vprint(v1);

	//尾删
	v1.pop_back();
	vprint(v1);
	
	v1.insert(v1.begin(), 10);//在起始位置插入10
	vprint(v1);

	v1.insert(v1.begin(), 2, 100);//在起始位置插入2个100
	vprint(v1);

	v1.erase(v1.begin());//删去v1.begin()指向的元素
	vprint(v1);

	v1.erase(v1.begin(), v1.end() - 1);//删去[v1.begin(),v1.end()-1)的数据
	vprint(v1);

	v1.clear();//清空
	vprint(v1);

}

int main()
{
	Test01();
	system("pause");
	return 0;
}