#pragma once
//使用BinTree实现PFC树
#include"BinTree.hpp"
//PFC树
typedef BinTree<char> PFCTree;

//使用Vector实现PFC森林
#include"Vector.hpp"
//PFC森林
typedef Vector<PFCTree*> PFCForest;

//使用位图结构实现二进制编码串
#include"Bitmap.hpp"
#include"Skiplist.hpp"
//PFC编码表，词条格式为：（key = 字符，value = 编码串）
typedef Skiplist<char, char*> PFCTable;

//只考虑可打印字符
#define N_CHAR (0x80 - 0x20)



//PFC编码森林初始化
PFCForest* initForest()
{
	PFCForest* forest = new PFCForest;//首先创建空森林，然后
	for (int i = 0; i < N_CHAR; ++i)//对每一个可打印字符[0x20, 0x80)
	{
		forest->insert(i, new PFCTree());//创建一棵对应的PFC编码树，初始时其中
		(*forest)[i]->insertAsRoot(0x20 + i);//只包含对应的一个(叶、根)节点
	}
	return forest;//返回包含N_CHAR棵树的森林，其中每棵树各包含一个字符
}

//构造PFC树
PFCTree* generateTree(PFCForest* forest)
{
	srand((unsigned int)time(nullptr));//这里将随机取树合并，故先设置随机种子
	while (1 < forest->size())//共做|forest|-1次合并
	{
		PFCTree* s = new PFCTree; s->insertAsRoot('^');//创建新树（根标记为“^”）
		Rank r1 = rand() % forest->size();//随机选取r1,且
		s->attachAsLC(s->root(), (*forest)[r1]);//作为左子树接入后
		forest->remove(r1);//随即剔除
		Rank r2 = rand() % forest->size();//随机选取r2,且
		s->attachAsRC(s->root(), (*forest)[r2]);//作为右子树接入后
		forest->remove(r2);//随即剔除
		forest->insert(forest->size(), s);//合并后的PFC树重新植入PFC森林
	}
	return (*forest)[0];//至此，森林中尚存的最后一棵树，即全局PFC编码树
}

//通过遍历获取各字符的编码
void generateCT(Bitmap* code, int length, PFCTable* table, BinNodePosi(char) v)
{
	if (IsLeaf(*v))//若是叶节点
	{ table->put(v->data, code->bits2string(length)); return; }
	if (HasLChild(*v))//left = 0
	{ code->clear(length); generateCT(code, length + 1, table, v->lc); }
	if (HasRChild(*v))//right = 1
	{ code->set(length);   generateCT(code, length + 1, table, v->rc); }
}

//构造PFC编码表
PFCTable* generateTable(PFCTree* tree)
{
	PFCTable* table = new PFCTable;//创建以Skiplist实现的编码表
	Bitmap* code = new Bitmap;//用于记录RPS的位图
	generateCT(code, 0, table, tree->root());//遍历以获取各字符（叶节点）
	release(code);//释放编码位图
	return table;//返回编码表
}

//PFC编码算法
int encode(PFCTable* table, Bitmap& codeString, char* s)
{
	int n = 0;
	for (size_t m = strlen(s), i = 0; i < m; ++i)
	{//对于明文s[]中的每个字符
		char** pCharCode = table->get(s[i]);//取出其对应的编码串
		if (!pCharCode)pCharCode = table->get(s[i] + 'A' - 'a');//小写字母转为大写字母
		if (!pCharCode)pCharCode = table->get(' ');//无法识别的字符统一视作空格
		printf("%s", *pCharCode);//输出当前字符的编码
		for (size_t m = strlen(*pCharCode), j = 0; j < m; ++j)//将当前字符的编码接入编码串
			'1' == *(*pCharCode + j) ? codeString.set(n++) : codeString.clear(n++);
	}
	return n;//二进制编码串记录于codeString中，返回编码串总长
}

//PFC解码算法
void decode(PFCTree* tree, Bitmap& code, int n)
{
	BinNodePosi(char) x = tree->root();//根据PFC编码树
	for (int i = 0; i < n; ++i)//将编码（二进制位图）
	{
		x = code.test(i) ? x->rc : x->lc;
		if (IsLeaf(*x))//转译为明码井
		{
			printf("%c", x->data); x = tree->root();
		}
	}
}