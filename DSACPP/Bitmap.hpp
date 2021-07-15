#define _CRT_SECURE_NO_WARNINGS 1
#include<memory>
//位图（Bitmap）是一种特殊的序列结构，可用以动态地表示由一组（无符号）整数构成的集合。
//其长度无限，且其中每个元素的取值均为布尔型（初始均为 false）
class Bitmap
{
private:
	//比特图所存放的空间M[]
	char* M;
	//容量为N*sizeof(char)*8比特
	int N;
protected:
	void init(int n){ M = new char[N = (n + 7) / 8]; memset(M, 0, N); }
public:
	//按指定或默认规模创建比特图(为测试暂时选用较小的默认值)
	Bitmap(int n = 8){ init(n); }
	//按指定或默认规模，从指定文件中读取比特图
	Bitmap(char* file, int n = 8)
	{
		init(n); 
		FILE* fp = fopen(file, "r"); 
		fread(M, sizeof(char), N, fp); 
		fclose(fp);
	}
	//析构时释放比特空间
	~Bitmap(){ delete[]M; M = nullptr; }

	//将第i位置为true （将整数i加入当前集合）
	void set  (int k){ expand(k);		 M[k >> 3] |=  (0x80 >> (k & 0x07)); }

	//将第i位置为false（从当前集合中删除整数i）
	void clear(int k){ expand(k);		 M[k >> 3] &=~ (0x80 >> (k & 0x07)); }

	//测试第i位是否为true（判断整数i是否属于当前集合）
	bool test (int k){ expand(k); return M[k >> 3] &   (0x80 >> (k & 0x07)); }

	//将位图整体导出至指定的文件，以便对此后的新位图批量初始化
	void dump(char* file)
	{
		FILE* fp = fopen(file, "w");
		fwrite(M, sizeof(char), N, fp);
		fclose(fp);
	}

	//将前n位转换位字符串
	char* bits2string(int n)
	{
		expand(n - 1);//此时可能被访问的最高位为bitmap[n - 1]
		char* s = new char[n + 1];//为字符串动态分配空间，由上层调用者负责释放
		s[n] = '\0';
		for (int i = 0; i < n; ++i)
			s[i] = test(i) ? '1' : '0';
		return s;//返回字符串位置
	}


	//若被访问的Bitmap[k]已出界，则需扩容
	void expand(int k)
	{
		if (k < 8 * N)
			return;//仍在界内，无需扩容
		int oldN = N;
		char* oldM = M;
		init(2 * k);//与向量类似，加倍策略
		memcpy_s(M, N, oldM, oldN);//原数据转移至新空间
		delete[] oldM;//释放旧空间
	}
};