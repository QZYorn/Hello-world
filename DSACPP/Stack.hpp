#pragma once
#include"ListNode.hpp"
#include"List.hpp"
#include"Vector.hpp"

template<class T>
class Stack :public Vector<T>
{
public:
	void push(T const &e){ insert(size(), e); }//��ջ
	T pop(){ return remove(size() - 1); }//��ջ
	T& top(){ return get(size() - 1); }//ȡ��
};

template<class T>
class LStack :public List<T>
{
public:
	void push(T const &e){ this->insertAsLast(e); }//��ջ
	T pop(){ return this->remove(last()); }//��ջ
	T& top(){ return last()->data; };//ȡ��
};






//Ӧ��
#define N_OPTR 9//���������
//             �ӣ������ˣ������˷����׳ˣ������ţ������ţ���ֹ������ֹ��
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE }Operator;
//��������ȼ��Ƚ�
const char pri[N_OPTR][N_OPTR] = {
	//          ������������������ǰ���������������������
	//           +    -    *    /    ^    !    (    )   \0
	/* |  + */	'>', '>', '<', '<', '<', '<', '<', '>', '>',
	/* |  - */  '>', '>', '<', '<', '<', '<', '<', '>', '>',
	/* ջ * */  '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/* �� / */  '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/* �� ^ */  '>', '>', '>', '>', '>', '<', '<', '>', '>',
	/* �� ! */  '>', '>', '>', '>', '>', '>', ' ', '>', '>',
	/* �� ( */  '<', '<', '<', '<', '<', '<', '<', '=', ' ',
	/* |  ) */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	/* | \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '=' };

//����ת��
void convert(Stack<char> &vs, int n, int base)
{
	static char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '\0' };
	while (n > 0)
	{
		vs.push(digit[n % base]);
		n /= base;
	}
}

//����ƥ��
bool paren(const char exp[], int lo, int hi)//exp[lo,hi)
{
	Stack<char> vs;
	while (lo++ < hi)
	{
		switch (exp[lo])
		{
		case '{':case'[':case'(':
			vs.push(exp[lo]);
			break;
		case')':
			if (!vs.size() || '(' != vs.pop())
				return false;
			break;
		case']':
			if (!vs.size() || '[' != vs.pop())
				return false;
			break;
		case'}':
			if (!vs.size() || '{' != vs.pop())
				return false;
			break;
		default://�������ַ�����
			break;
		}
	}
	return !vs.size();
}
//ջ��ϴ
bool stackPermutation(int B[], int n)
{
	Stack<int> S;
	Stack<int> A;
	int i = 0;
	for (int k = n; 0 < k; k--)
		A.push(k);//<1,2,3,4,5,6...]

	while (A.size() || S.size())//A SͬʱΪ��ʱ�˳�ѭ��
	{
		if (A.size() && (!S.size() || B[i] != S.top()))//A��Ϊ�� ���� SΪ�� ���� Sջ����ΪBջ��ʱ
			S.push(A.pop());//A��ջ ��ѹ�� S��
		else if (S.size() && B[i] == S.top())//S��Ϊ�� ���� Sջ����ΪBջ��ʱ
		{
			S.pop();//S��ջ
			i++;    //B��ջ
		}
		else//AΪ�� �� Sջ����ΪBջ��
		{
			return false;
		}
	}
	return true;

}
//�����ת��Ϊ����
Operator optrRank(char op)
{

	switch (op)
	{
	case '+':
		return ADD;
	case '-':
		return SUB;
	case '*':
		return MUL;
	case '/':
		return DIV;
	case '^':
		return POW;
	case '!':
		return FAC;
	case '(':
		return L_P;
	case ')':
		return R_P;
	case '\0':
		return EOE;
	default:
		exit(-1);
	}
}
//������Ƚ�
char orderBetween(char L, char R)
{
	return pri[optrRank(L)][optrRank(R)];
}
//һԪ�������׳�
float calcu(char op, float sum)
{
	int src = 1;

	switch (op)
	{
	case '!':
		while (sum-- > 0)
			src *= (int)sum;
	default:
		exit(-1);
	}

	return (float)src;
}
//��Ԫ������
float calcu(char op, float sum1, float sum2)
{
	float tmp = sum1;

	switch (op)
	{
	case '+':
		return sum1 + sum2;
	case '-':
		return sum1 - sum2;
	case '*':
		return sum1 * sum2;
	case '/':
		return sum1 / sum2;
	case '^':
		while (sum2--)
		{
			sum1 *= tmp;
		}
		return sum1;
	default:
		exit(-1);
	}
}
//�����ַ�ת��Ϊ����
void  readNum(char* &S, Stack<float> &opnd)
{
	float src = *S - '0';

	while (isdigit(*(++S)))
	{	//123.456
		src *= 10;
		//0
		//10
		//120
		src += (*S - '0');
		//1
		//12
		//123
	}
	if (*S != '.')
	{
		opnd.push(src);
		return;
	}

	float i = 1;
	while (isdigit(*(++S)))
	{
		src += (*S - '0') * (i /= 10);
	}
	opnd.push(src);
}
//������������RPNĩβ
void append(char* &RPN, float opnd)
{
	char buf[64];
	if (0.0 < opnd - (int)opnd)//С��
		sprintf(buf, "%.2f \0", opnd);
	else//����
		sprintf(buf, "%d \0", (int)opnd);
	RPN = (char*)realloc(RPN, sizeof(char)*(strlen(buf) + strlen(RPN) + 1));//��չ�ռ�
	strcat(RPN, buf);
}
//������������RPNĩβ
void append(char* &RPN, char optr)
{
	int n = strlen(RPN);
	RPN = (char*)realloc(RPN, sizeof(char)*(n + 3));
	sprintf(RPN + n, "%c \0", optr);
}

float evaluate(char* S, char* &RPN)
{
	Stack<char> optr;//�����ջ
	Stack<float> opnd;//������ջ
	optr.push('\0');

	while (optr.size())//optrΪ��ʱ�˳�ѭ��
	{
		if (isdigit(*S))//һֱ������ջ�ֱ�����������
		{
			readNum(S, opnd);
			append(RPN, opnd.top());
		}
		else
		{
			char op = optr.top();
			switch (orderBetween(op, *S))
			{
			case '>'://��ʼ��֮ǰ����

				if (op == '!')
					opnd.push(calcu(optr.pop(), opnd.pop()));
				else
				{
					float op2 = opnd.pop();
					float op1 = opnd.pop();
					opnd.push(calcu(optr.pop(), op1, op2));
				}
				append(RPN, op);
				break;
			case '<'://ѹ��ȥ
				optr.push(*S);
				S++;
				break;

			case '=':
				optr.pop();
				S++;
				break;

			default:
				exit(-1);
			}

		}

	}
	return opnd.pop();
}


void test1()
{
	Stack<int> vs1;

	vs1.push(1);
	vs1.push(6);
	vs1.push(6);
	vs1.top()++;
	vs1.pop();

	LStack<int> ls1;
	ls1.push(1);
	ls1.push(6);
	ls1.push(6);
	ls1.top()++;
	ls1.pop();
}

void test2()//���Խ���ת��
{
	Stack<char> vs;
	int source, base;
	cout << "��ת����ʮ��������";
	cin >> source;
	cout << "��ת���Ľ��ƣ�";
	cin >> base;
	convert(vs, source, base);
	cout << "ת���������Ϊ��";
	while (vs.size())
	{
		cout << vs.pop();
	}
}

void test3()//��������ƥ��
{
	char a[] = "a / ( b [ i - 1 ] [ j + 1 ] + c [ i + 1 ] [ j - 1 ] ) * 2";
	char b[] = "a / ( b [ i - 1 ] [ j + 1 ] ) + c [ i + 1 ] [ j - 1 ] ) * 2";

	bool flag = paren(a, 0, sizeof(a));
	string str = flag ? "��ȫƥ��" : "ʧ��";
	cout << "a[]";
	for (char c : str)
		cout << c;
	cout << endl;

	flag = paren(b, 0, sizeof(b));
	str = flag ? "��ȫƥ��" : "ʧ��";
	cout << "b[]";
	for (char c : str)
		cout << c;
	cout << endl;
}

void test4()
{
	int B[] = { 4, 3, 2, 1, 5, 6, 7 };//[ 4 3 2 1 5 6 7 >
	stackPermutation(B, sizeof(B) / sizeof(B[0]));
}

void test5()
{
	char S[] = "((0+(1+23)/4*5*67-8+9))";

	char* RPN = (char*)malloc(10);
	RPN[0] = '\0';
	cout << evaluate(S, RPN) << endl;
}
