#include<iostream>
#include<string>
using namespace std;

class Test
{
	//����
public:
	string t_name;

	//����
protected:
	string t_car;

	//˽��
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