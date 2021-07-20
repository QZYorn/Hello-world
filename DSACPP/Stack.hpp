#pragma once
#include"ListNode.hpp"
#include"List.hpp"
#include"Vector.hpp"

template<class T>
class Stack :public Vector<T>
{
public:
	void push(T const &e){ insert(size(), e); }//入栈
	T pop(){ return remove(size() - 1); }//出栈
	T& top(){ return get(size() - 1); }//取顶
};

template<class T>
class LStack :public List<T>
{
public:
	void push(T const &e){ this->insertAsLast(e); }//入栈
	T pop(){ return this->remove(last()); }//出栈
	T& top(){ return last()->data; };//取顶
};






//应用
#define N_OPTR 9//运算符总数
//             加，减，乘，除，乘方，阶乘，左括号，右括号，起止符和终止符
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE }Operator;
//运算符优先级比较
const char pri[N_OPTR][N_OPTR] = {
	//          ————————当前运算符————————
	//           +    -    *    /    ^    !    (    )   \0
	/* |  + */	'>', '>', '<', '<', '<', '<', '<', '>', '>',
	/* |  - */  '>', '>', '<', '<', '<', '<', '<', '>', '>',
	/* 栈 * */  '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/* 顶 / */  '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/* 运 ^ */  '>', '>', '>', '>', '>', '<', '<', '>', '>',
	/* 算 ! */  '>', '>', '>', '>', '>', '>', ' ', '>', '>',
	/* 符 ( */  '<', '<', '<', '<', '<', '<', '<', '=', ' ',
	/* |  ) */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	/* | \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '=' };

//进制转换
void convert(Stack<char> &vs, int n, int base)
{
	static char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '\0' };
	while (n > 0)
	{
		vs.push(digit[n % base]);
		n /= base;
	}
}

//括号匹配
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
		default://非括号字符跳过
			break;
		}
	}
	return !vs.size();
}
//栈混洗
bool stackPermutation(int B[], int n)
{
	Stack<int> S;
	Stack<int> A;
	int i = 0;
	for (int k = n; 0 < k; k--)
		A.push(k);//<1,2,3,4,5,6...]

	while (A.size() || S.size())//A S同时为空时退出循环
	{
		if (A.size() && (!S.size() || B[i] != S.top()))//A不为空 并且 S为空 或者 S栈顶不为B栈底时
			S.push(A.pop());//A出栈 并压到 S里
		else if (S.size() && B[i] == S.top())//S不为空 并且 S栈顶即为B栈底时
		{
			S.pop();//S出栈
			i++;    //B入栈
		}
		else//A为空 且 S栈顶不为B栈底
		{
			return false;
		}
	}
	return true;

}
//运算符转换为数字
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
//运算符比较
char orderBetween(char L, char R)
{
	return pri[optrRank(L)][optrRank(R)];
}
//一元操作符阶乘
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
//二元操作符
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
//数字字符转换为整型
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
//将操作数接至RPN末尾
void append(char* &RPN, float opnd)
{
	char buf[64];
	if (0.0 < opnd - (int)opnd)//小数
		sprintf(buf, "%.2f \0", opnd);
	else//整数
		sprintf(buf, "%d \0", (int)opnd);
	RPN = (char*)realloc(RPN, sizeof(char)*(strlen(buf) + strlen(RPN) + 1));//扩展空间
	strcat(RPN, buf);
}
//将操作数接至RPN末尾
void append(char* &RPN, char optr)
{
	int n = strlen(RPN);
	RPN = (char*)realloc(RPN, sizeof(char)*(n + 3));
	sprintf(RPN + n, "%c \0", optr);
}

float evaluate(char* S, char* &RPN)
{
	Stack<char> optr;//运算符栈
	Stack<float> opnd;//运算数栈
	optr.push('\0');

	while (optr.size())//optr为空时退出循环
	{
		if (isdigit(*S))//一直读数到栈里，直到遇到运算符
		{
			readNum(S, opnd);
			append(RPN, opnd.top());
		}
		else
		{
			char op = optr.top();
			switch (orderBetween(op, *S))
			{
			case '>'://开始算之前的数

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
			case '<'://压进去
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

void test2()//测试进制转换
{
	Stack<char> vs;
	int source, base;
	cout << "需转换的十进制数：";
	cin >> source;
	cout << "需转换的进制：";
	cin >> base;
	convert(vs, source, base);
	cout << "转换后的数字为：";
	while (vs.size())
	{
		cout << vs.pop();
	}
}

void test3()//测试括号匹配
{
	char a[] = "a / ( b [ i - 1 ] [ j + 1 ] + c [ i + 1 ] [ j - 1 ] ) * 2";
	char b[] = "a / ( b [ i - 1 ] [ j + 1 ] ) + c [ i + 1 ] [ j - 1 ] ) * 2";

	bool flag = paren(a, 0, sizeof(a));
	string str = flag ? "完全匹配" : "失配";
	cout << "a[]";
	for (char c : str)
		cout << c;
	cout << endl;

	flag = paren(b, 0, sizeof(b));
	str = flag ? "完全匹配" : "失配";
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
