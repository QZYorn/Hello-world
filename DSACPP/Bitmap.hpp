#define _CRT_SECURE_NO_WARNINGS 1
#include<memory>
//λͼ��Bitmap����һ����������нṹ�������Զ�̬�ر�ʾ��һ�飨�޷��ţ��������ɵļ��ϡ�
//�䳤�����ޣ�������ÿ��Ԫ�ص�ȡֵ��Ϊ�����ͣ���ʼ��Ϊ false��
class Bitmap
{
private:
	//����ͼ����ŵĿռ�M[]
	char* M;
	//����ΪN*sizeof(char)*8����
	int N;
protected:
	void init(int n){ M = new char[N = (n + 7) / 8]; memset(M, 0, N); }
public:
	//��ָ����Ĭ�Ϲ�ģ��������ͼ(Ϊ������ʱѡ�ý�С��Ĭ��ֵ)
	Bitmap(int n = 8){ init(n); }
	//��ָ����Ĭ�Ϲ�ģ����ָ���ļ��ж�ȡ����ͼ
	Bitmap(char* file, int n = 8)
	{
		init(n); 
		FILE* fp = fopen(file, "r"); 
		fread(M, sizeof(char), N, fp); 
		fclose(fp);
	}
	//����ʱ�ͷű��ؿռ�
	~Bitmap(){ delete[]M; M = nullptr; }

	//����iλ��Ϊtrue ��������i���뵱ǰ���ϣ�
	void set  (int k){ expand(k);		 M[k >> 3] |=  (0x80 >> (k & 0x07)); }

	//����iλ��Ϊfalse���ӵ�ǰ������ɾ������i��
	void clear(int k){ expand(k);		 M[k >> 3] &=~ (0x80 >> (k & 0x07)); }

	//���Ե�iλ�Ƿ�Ϊtrue���ж�����i�Ƿ����ڵ�ǰ���ϣ�
	bool test (int k){ expand(k); return M[k >> 3] &   (0x80 >> (k & 0x07)); }

	//��λͼ���嵼����ָ�����ļ����Ա�Դ˺����λͼ������ʼ��
	void dump(char* file)
	{
		FILE* fp = fopen(file, "w");
		fwrite(M, sizeof(char), N, fp);
		fclose(fp);
	}

	//��ǰnλת��λ�ַ���
	char* bits2string(int n)
	{
		expand(n - 1);//��ʱ���ܱ����ʵ����λΪbitmap[n - 1]
		char* s = new char[n + 1];//Ϊ�ַ�����̬����ռ䣬���ϲ�����߸����ͷ�
		s[n] = '\0';
		for (int i = 0; i < n; ++i)
			s[i] = test(i) ? '1' : '0';
		return s;//�����ַ���λ��
	}


	//�������ʵ�Bitmap[k]�ѳ��磬��������
	void expand(int k)
	{
		if (k < 8 * N)
			return;//���ڽ��ڣ���������
		int oldN = N;
		char* oldM = M;
		init(2 * k);//���������ƣ��ӱ�����
		memcpy_s(M, N, oldM, oldN);//ԭ����ת�����¿ռ�
		delete[] oldM;//�ͷžɿռ�
	}
};