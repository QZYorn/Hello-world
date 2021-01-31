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
	//Î²²å
	d1.push_back(10);
	d1.push_back(20);

	//Í·²å
	d1.push_front(100);
	d1.push_front(200);
	printDeque(d1);
	//200 100 10 20

	//Î²É¾
	d1.pop_back();
	//200 100 10
	printDeque(d1);

	//Í·É¾
	d1.pop_front();
	//100 10
	printDeque(d1);

	deque<int>::iterator it = d1.begin();
	d1.insert(it+1, 5);
	//100 5 10
	printDeque(d1);

	it = d1.begin();
	d1.insert(it+1, 3, 6);
	//100 6 6 6 5 10
	printDeque(d1);

	deque<int> d2;
	d2.insert(d2.begin(),5, 99);
	//99,99,99,99,99
	printDeque(d2);
	d2.insert(d2.begin()+1,d1.begin()+1,d1.end()-2);
	//99 6 6 6 99 99 99 99
	printDeque(d2);

	d2.erase(d2.begin()+4);
	//99 6 6 6 99 99 99
	printDeque(d2);

	d2.erase(d2.begin() + 1, d2.begin() + 4);
	//99 99 99 99 
	printDeque(d2);

	d2.clear();
	printDeque(d2);

}



int main()
{
	Test01();
	system("pause");
	return 0;
}