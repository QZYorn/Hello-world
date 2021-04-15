#define _CRT_SECURE_NO_WARNINGS 1
#define _SCL_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
//#include<iterator>
#include<sstream>
#include<vector>
//#include<list>
//#include<map>
//#include<set>
//#include<deque>
//#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
#include<memory>
//#include<stdlib.h>
#include<tuple>
#include<bitset>
#include<random>
#include<ctime>
#include<iomanip>
#include"Sales_data.h"
using namespace std;
//using namespace std::placeholders;


bool compareIsbn(const Sales_data &s1, const Sales_data &s2)
{
	return s1.isbn() == s2.isbn();
}



//17.4
//matches������Ա����������������ָ�����vector��Ԫ�صĵ�����
typedef	tuple<vector<Sales_data>::size_type,
			  vector<Sales_data>::const_iterator,
			  vector<Sales_data>::const_iterator> matches;
//files����ÿ�ҵ�����ۼ�¼
//findBook����һ��vector,����ÿһ����Ա���������˸����鼮��һ�����
vector<matches> 
findBook(const vector<vector<Sales_data>> &files,
		 const string &book)
{
	vector<matches> ret;
	for (auto it = files.cbegin(); it != files.cend(); ++it)//ÿһ�����
	{
		auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);//��ÿ�����ISBN�Ƚϲ����ط�Χ
		if (found.first != found.second)
			ret.push_back(make_tuple(it - files.cbegin(), found.first, found.second));
	}
	return ret;
}

void reportResult(istream &is, ostream &os, const vector<vector<Sales_data>> &files)
{
	string s;
	while (is >> s)
	{
		auto trans = findBook(files, s);
		if (trans.empty())
		{
			cout << s << " not found in any stores" << endl;
			continue;
		}
		for (const auto &store : trans)//��������ÿһ�ҵ�
		{
			os << "store " << get<0>(store) << " sales: "
			   << accumulate(get<1>(store), get<2>(store), Sales_data(s)) << endl;
		}
	}
}

//17.5
typedef	pair<vector<Sales_data>::size_type,pair<
	vector<Sales_data>::const_iterator,
	vector<Sales_data>::const_iterator>> matches2;
vector<matches2>
findBook2(const vector<vector<Sales_data>> &files,
const string &book)
{
	vector<matches2> ret;
	for (auto it = files.cbegin(); it != files.cend(); ++it)//ÿһ�����
	{
		auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);//��ÿ�����ISBN�Ƚϲ����ط�Χ
		if (found.first != found.second)
			ret.push_back(make_pair(it - files.cbegin(),make_pair(found.first, found.second)));
	}
	return ret;
}

//17.6
struct matches3
{
	vector<Sales_data>::size_type sz;
	vector<Sales_data>::const_iterator beg;
	vector<Sales_data>::const_iterator end;
};
vector<matches3>
findBook3(const vector<vector<Sales_data>> &files,
const string &book)
{
	vector<matches3> ret;
	for (auto it = files.cbegin(); it != files.cend(); ++it)//ÿһ�����
	{
		auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);//��ÿ�����ISBN�Ƚϲ����ط�Χ
		if (found.first != found.second)
			ret.push_back(matches3{ it - files.cbegin(), found.first, found.second });
	}
	return ret;
}

//17.11
struct Exam
{
	
	Exam(const unsigned &a) :_answer(a){}
	void change(const unsigned &No, const bool &TN)
	{
		_answer[No - 1] = TN;
	}
	ostream &print(ostream &os)
	{
		return os << _answer << " ";
	}
	bitset<100> _answer;
};

unsigned my_random(const unsigned &seed, const unsigned &min, const unsigned &max)
{
	static default_random_engine e(seed);//���������
	static uniform_int_distribution<unsigned> u(min, max);//������ֲ���
	default_random_engine::result_type i = u(e);
	return i;
}

void test17()
{
	//17.1.1
	cout << ">>>>>>>>>-----  17.1.1  -----<<<<<<<<<" << endl;
	//17.1
	tuple<int, int, int> iii(10, 20, 30);
	//17.2
	tuple<string, vector<string>, pair<string, int>> svp;
	//17.9
	string bstr;
	//cin >> bstr;
	bitset<8> bv(bstr);
	//cout << bv << endl;

	//17.10
	bitset<22> bv21;
	bv21.set(1);
	bv21.set(2);
	bv21.set(3);
	bv21.set(5);
	bv21.set(8);
	bv21.set(13);
	bv21.set(21);

	//17.13
	unsigned a = 1<<1|1<<2|1<<3;
	Exam ax(a);
	ax.change(5,true);
	ax.print(cout);

	//17.28
	cout << endl;
	cout << my_random(time(0), 0, 15);

	//��̬�ֲ�200������(4,1.5) ��ֵ4 ��׼��1.5 ����·ֲ���� 
	default_random_engine e(time(0));
	normal_distribution<> n(4, 1.5);
	vector<unsigned> vals(9);//�Ÿ�Ԫ��Ĭ��Ϊ0
	for (size_t i = 0; i != 200; ++i)
	{
		unsigned v = lround(n(e));//���뵽���������
		if (v < vals.size())//�޶�����ڷ�Χ��
			++vals[v];//ͳ��ÿ�������ִ���
	}
	cout << endl;
	for (size_t i = 0; i != vals.size(); ++i)
	{
		cout << i << "��" << string(vals[i], '*') << endl;
	}

	//17.34
	int i = -16;
	double d = 3.14159;
	cout << boolalpha
		<< true << " "
		<< false << noboolalpha << endl;
	cout << showbase
		<< hex << "hex��"
		<< "i��" << i << " "
		<< "\td��" << d << endl
		<< oct << "oct��"
		<< "i��" << i << " "
		<< "\td��" << d << dec << noshowbase << endl;
	cout << showbase << uppercase
		<< hex << "hex��"
		<< "i��" << i << " "
		<< "\td��" << d << endl
		<< oct << "oct��"
		<< "i��" << i << " "
		<< "\td��" << d << dec << noshowbase << endl;
	cout << showbase << showpos //��ʾ����ǰ׺����ʾ����
		<< hexfloat << "hex��" << left << setfill('#')//�����,�ո��Ϊ���#
		<< "i��" << setw(10) << i << " "
		<< "d��" << setw(10) << d << endl
		<< fixed << "fix��" << right << setfill(' ')//�Ҷ��룬���#��Ϊ�ո�
		<< "i��" << setw(10) << i << " "
		<< "d��" << setw(10) << d << endl
		<< scientific << "sci��" << setprecision(3)<< internal//���������ȵ�Ϊ3��������ֵ֮�����ո�
		<< "i��" << setw(10) << i << ends
		<< "d��" << setw(10) << d <<endl
		<< defaultfloat << "bin��" << setbase(16)//������16�������
		<< "i��" << setw(10) << i << " "
		<< "d��" << setw(10) << d  << noshowbase << noshowpos << endl;

	//17.37
	cout << endl;
	ifstream ifs("test.txt",fstream::in);
	if (!ifs.is_open())
	{
		cout << "error open file" << endl;
		return ;
	}
	vector<string> vs;
	char arr[20] = {};
	int ch = 0;
	while (ifs.getline(arr,20,'\n').good())
	{
		vs.push_back(string(arr));
	}
	ifs.close();

	//17.39
	fstream fs("seek.txt", fstream::ate | fstream::in | fstream::out);//��λ�ļ�β�Լ���д�ķ�ʽ��
	if (!fs.is_open())
	{
		cout << "error open seek.txt" << endl;
		return;
	}
	auto f_end = fs.tellp();//��¼�ļ�β����λ��
	fs.seekp(0,fstream::beg);//�ض�λ���ļ���
	size_t count = 0;//ÿ�е��ֽ��ۼ���
	string line;//���浱ǰ��ȡ��
	while (fs.good() && fs.tellp() != f_end && getline(fs, line))//��ǰλ�ò�Ϊԭ�ļ�β  ����(Ȼ��) ��ȡ��һ�� ���� �ļ���������
	{
		count += line.size() + 1;//�ۼ�������ÿһ�г��� �Լ� 1λ���з�
		auto f_cur = fs.tellp();//��¼�ļ�����ǰλ��
		fs.seekp(0, fstream::end);//��λ���ļ�β
		fs << count;//���ļ�β���뵱ǰ�ֽ���
		if (f_cur != f_end)//��ԭ�ļ���λ�� ��Ϊ ԭ�ļ�β
			fs << " ";//����ո�
		fs.seekp(f_cur);//�ļ�����λ��ԭλ��
	}
	fs.seekp(0, fstream::end);//��λ���ļ�β
	fs << '\n';//����һ�����з�
	fs.close();
}

int main()
{
	test17();
	return 0;
}