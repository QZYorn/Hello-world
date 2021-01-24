#include<iostream>
#include<string>
using namespace std;

class Test
{
	//公开
public:
	string t_name;

	//保护
protected:
	string t_car;

	//私有
private:
	int t_password;

public:
	void Init()
	{
		t_name = "zhangsan";
		t_car = "benchi";
		t_password = 21321231;
	}
};

int main()
{
	Test t1;
	t1.Init();
	t1.t_name = "lisi";
	
	cout << t1.t_name << endl;
	/*cout << t1.t_car << endl;
	cout << t1.t_password << endl;*/
	return 0;
}