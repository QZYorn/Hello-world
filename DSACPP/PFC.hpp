#pragma once
//ʹ��BinTreeʵ��PFC��
#include"BinTree.hpp"
//PFC��
typedef BinTree<char> PFCTree;

//ʹ��Vectorʵ��PFCɭ��
#include"Vector.hpp"
//PFCɭ��
typedef Vector<PFCTree*> PFCForest;

//ʹ��λͼ�ṹʵ�ֶ����Ʊ��봮
#include"Bitmap.hpp"
#include"Skiplist.hpp"
//PFC�����������ʽΪ����key = �ַ���value = ���봮��
typedef Skiplist<char, char*> PFCTable;

//ֻ���ǿɴ�ӡ�ַ�
#define N_CHAR (0x80 - 0x20)



//PFC����ɭ�ֳ�ʼ��
PFCForest* initForest()
{
	PFCForest* forest = new PFCForest;//���ȴ�����ɭ�֣�Ȼ��
	for (int i = 0; i < N_CHAR; ++i)//��ÿһ���ɴ�ӡ�ַ�[0x20, 0x80)
	{
		forest->insert(i, new PFCTree());//����һ�ö�Ӧ��PFC����������ʼʱ����
		(*forest)[i]->insertAsRoot(0x20 + i);//ֻ������Ӧ��һ��(Ҷ����)�ڵ�
	}
	return forest;//���ذ���N_CHAR������ɭ�֣�����ÿ����������һ���ַ�
}

//����PFC��
PFCTree* generateTree(PFCForest* forest)
{
	srand((unsigned int)time(nullptr));//���ｫ���ȡ���ϲ������������������
	while (1 < forest->size())//����|forest|-1�κϲ�
	{
		PFCTree* s = new PFCTree; s->insertAsRoot('^');//���������������Ϊ��^����
		Rank r1 = rand() % forest->size();//���ѡȡr1,��
		s->attachAsLC(s->root(), (*forest)[r1]);//��Ϊ�����������
		forest->remove(r1);//�漴�޳�
		Rank r2 = rand() % forest->size();//���ѡȡr2,��
		s->attachAsRC(s->root(), (*forest)[r2]);//��Ϊ�����������
		forest->remove(r2);//�漴�޳�
		forest->insert(forest->size(), s);//�ϲ����PFC������ֲ��PFCɭ��
	}
	return (*forest)[0];//���ˣ�ɭ�����д�����һ��������ȫ��PFC������
}

//ͨ��������ȡ���ַ��ı���
void generateCT(Bitmap* code, int length, PFCTable* table, BinNodePosi(char) v)
{
	if (IsLeaf(*v))//����Ҷ�ڵ�
	{ table->put(v->data, code->bits2string(length)); return; }
	if (HasLChild(*v))//left = 0
	{ code->clear(length); generateCT(code, length + 1, table, v->lc); }
	if (HasRChild(*v))//right = 1
	{ code->set(length);   generateCT(code, length + 1, table, v->rc); }
}

//����PFC�����
PFCTable* generateTable(PFCTree* tree)
{
	PFCTable* table = new PFCTable;//������Skiplistʵ�ֵı����
	Bitmap* code = new Bitmap;//���ڼ�¼RPS��λͼ
	generateCT(code, 0, table, tree->root());//�����Ի�ȡ���ַ���Ҷ�ڵ㣩
	release(code);//�ͷű���λͼ
	return table;//���ر����
}

//PFC�����㷨
int encode(PFCTable* table, Bitmap& codeString, char* s)
{
	int n = 0;
	for (size_t m = strlen(s), i = 0; i < m; ++i)
	{//��������s[]�е�ÿ���ַ�
		char** pCharCode = table->get(s[i]);//ȡ�����Ӧ�ı��봮
		if (!pCharCode)pCharCode = table->get(s[i] + 'A' - 'a');//Сд��ĸתΪ��д��ĸ
		if (!pCharCode)pCharCode = table->get(' ');//�޷�ʶ����ַ�ͳһ�����ո�
		printf("%s", *pCharCode);//�����ǰ�ַ��ı���
		for (size_t m = strlen(*pCharCode), j = 0; j < m; ++j)//����ǰ�ַ��ı��������봮
			'1' == *(*pCharCode + j) ? codeString.set(n++) : codeString.clear(n++);
	}
	return n;//�����Ʊ��봮��¼��codeString�У����ر��봮�ܳ�
}

//PFC�����㷨
void decode(PFCTree* tree, Bitmap& code, int n)
{
	BinNodePosi(char) x = tree->root();//����PFC������
	for (int i = 0; i < n; ++i)//�����루������λͼ��
	{
		x = code.test(i) ? x->rc : x->lc;
		if (IsLeaf(*x))//ת��Ϊ���뾮
		{
			printf("%c", x->data); x = tree->root();
		}
	}
}