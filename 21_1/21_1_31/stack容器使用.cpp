#include<iostream>
using namespace std;
#include<stack>

void Test01()
{
	stack<int> stk;
	stk.push(10);
	stk.push(20);
	stk.push(30);
	stk.push(40);
	stk.push(50);

	while (!stk.empty())
	{
		cout << "ջ��Ϊ" << stk.top() << endl;
		stk.pop();//��ջ
		cout << "ջ�Ĵ�СΪ��" << stk.size() << endl;

	}
	cout << "ջ�Ĵ�СΪ��" << stk.size() << endl;
}



int main()
{
	Test01();
	system("pause");
	return 0;
}