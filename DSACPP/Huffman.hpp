#define N_CHAR (0x80 - 0x20)//���Կɴ�ӡ�ַ�Ϊ��
//Huffman(��)�ַ�
struct HuffChar
{
	char ch;//�ַ�
	int weight;//Ƶ��
	HuffChar(char c = '^', int w = 0) : ch(c), weight(w){};
	//�Ƚ���
	bool operator<(HuffChar const& hc){ return weight > hc.weight; }//�˴������С�ߵ���Ȩ�ظ�С�����ȼ�����
	//�е���
	bool operator==(HuffChar const& hc){ return weight == hc.weight; }
};
#include"BinTree.hpp"
#define HuffTree BinTree<HuffChar> //Huffman������BinTree�������ڵ�����ΪHuffChar

#include"List.hpp"//��Listʵ��
#define ListNodePosi(T) ListNode<T>*
typedef List<HuffTree*> HuffForest;//Huffmanɭ��

#include"Bitmap.hpp"//����Bitmapʵ��
typedef Bitmap HuffCode;//Huffman�����Ʊ���

#include"Hashtable.hpp"//��Hashtableʵ��
typedef Hashtable<char, char*> HuffTable;//Huffman�����

//ͳ���ַ�����Ƶ��
int* statistics(char* sample_text_file)
{
	int* freq = new int[N_CHAR];//����ͳ����������ʣ����������¼���ַ����ִ���
	memset(freq, 0, sizeof(int)*N_CHAR);//����
	FILE* fp = fopen(sample_text_file, "r");//assert:�ļ������ҿ���ȷ��
	for (char ch; 0 < fscanf(fp, "%c", &ch);)//���ɨ�������ļ��е�ÿ���ַ�
		if (ch >= 0x20)freq[ch - 0x20]++;//�ۼƶ�Ӧ�ĳ��ִ���
	fclose(fp); 
	return freq;
}

//����Ƶ��ͳ�Ʊ�Ϊÿ���ַ�����һ����
HuffForest* initForest(int* freq)
{
	HuffForest* forest = new HuffForest;//��List��ʵ�ֵ�Huffmanɭ��
	for (int i = 0; i < N_CHAR; ++i)//Ϊÿ���ַ�
	{
		forest->insertAsLast(new HuffTree);//����һ�����������ַ�����Ƶ��
		forest->last()->data->insertAsRoot(HuffChar(0x20 + i, freq[i]));//��������
	}
	return forest;
}


//��Huffmanɭ�����ҳ�Ȩ����С�ģ������ַ�
HuffTree* minHChar(HuffForest* forest)
{
	ListNodePosi(HuffTree*) p = forest->first();//���׽ڵ��������
	ListNodePosi(HuffTree*) minChar = p;//��СHuffman�����ڵĽڵ�λ��
	int minWeight = p->data->root()->data.weight;//Ŀǰ����СȨ��
	while (forest->valid(p = p->succ))//�������нڵ�
	{
		if (minWeight > p->data->root()->data.weight)//����ǰ�ڵ���������С����
		{
			minWeight = p->data->root()->data.weight;
			minChar = p;//���¼�¼
		}
	}
	return forest->remove(minChar);//����ѡ����Huffman����ɭ����ժ����������
}

//Huffman�����㷨
HuffTree* generateTree(HuffForest* forest)
{
	while (1 < forest->size())
	{
		HuffTree* T1 = minHChar(forest); HuffTree* T2 = minHChar(forest);
		HuffTree* S = new HuffTree();
		S->insertAsRoot(HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
		S->attachAsLC(S->root(), T1); S->attachAsRC(S->root(), T2);
		forest->insertAsLast(S);
	}//assset:ѭ������ʱ��ɭ����Ψһ���б��׽ڵ��У����ǿ�����Huffman������
	return forest->first()->data;
}

//ͨ��������ȡ���ַ��ı���
static void generateCT(Bitmap* code, int length, HuffTable* table, BinNodePosi(HuffChar) v)
{
	if (IsLeaf(*v))//����Ҷ�ڵ�
	{
		table->put(v->data.ch, code->bits2string(length)); return;
	}
	if (HasLChild(*v))//left = 0
	{
		code->clear(length); generateCT(code, length + 1, table, v->lc);
	}
	if (HasRChild(*v))//right = 1
	{
		code->set(length);   generateCT(code, length + 1, table, v->rc);
	}
}

//�����ַ�����ͳһ������ɢ�б�ʵ�ֵı������
HuffTable* generateTable(HuffTree* tree)
{
	HuffTable* table = new HuffTable; 
	Bitmap* code = new Bitmap;
	generateCT(code, 0, table, tree->root());
	release(code);
	return table;
}

//���ձ�����Bitmap������
int encode(HuffTable* table, Bitmap* codeString, char* s)
{
	int n = 0;//�����صı��봮�ܳ�n
	for (size_t m = strlen(s), i = 0; i < m; ++i)
	{//��������s[]�е�ÿ���ַ�
		char** pCharCode = table->get(s[i]);//ȡ�����Ӧ�ı��봮
		if (!pCharCode)pCharCode = table->get(s[i] + 'A' - 'a');//Сд��ĸתΪ��д��ĸ
		if (!pCharCode)pCharCode = table->get(' ');//�޷�ʶ����ַ�ͳһ�����ո�
		printf("%s", *pCharCode);//�����ǰ�ַ��ı���
		for (size_t m = strlen(*pCharCode), j = 0; j < m; ++j)//����ǰ�ַ��ı��������봮
			'1' == *(*pCharCode + j) ? codeString->set(n++) : codeString->clear(n++);
	}
	printf("\n");
	return n;//�����Ʊ��봮��¼��codeString�У����ر��봮�ܳ�
}

//���ݱ������Գ�Ϊn��Bitmap������
void decode(HuffTree* tree, Bitmap* code, int n)
{
	BinNodePosi(HuffChar) x = tree->root();
	for (int i = 0; i < n; ++i)//�����루������λͼ��
	{
		x = code->test(i) ? x->rc : x->lc;
		if (IsLeaf(*x))//ת��Ϊ���뾮
		{
			printf("%c", x->data.ch); x = tree->root();
		}
	}
}//��������룬�ڴ�ֱ�Ӵ�ӡ�����ʵ���пɸ�Ϊ������Ҫ�����ϲ������