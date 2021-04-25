#pragma once
#include"Vector.hpp"
#include"Graph.hpp"
#include<assert.h>


template<typename Tv>//顶点对象
struct Vertex		
{
	Tv data;//数据域
	int inDegree, outDegree;//入度，出度
	VStatus status;//状态
	int dTime, fTime;//时间标签
	int parent;  //在遍历树中的父节点
	int priority;//在遍历树中的优先级数
	Vertex(Tv const &tv = (Tv)0) ://构造新顶点
		data(tv), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};


template<typename Te>//边对象
struct Edge			
{
	Te data;   //数据域
	int weight;//权重
	EType type;//类型
	Edge(Te const&te, int w) ://构造新边
		data(te), weight(w), type(UNDETERMINED){}
};




template<typename Tv, typename Te>//邻接矩阵
class GraphMatrix :public Graph<Tv, Te>
{
private:
	Vector<Vertex<Tv>> V;		  //顶点集(向量)
	Vector < Vector<Edge<Te>*>> E;//边集(邻接矩阵)
public:
	GraphMatrix(){ n = e = 0; }//构造函数
	~GraphMatrix()//析构函数
	{ 
		for (int i = 0; i < n;++i)
			for (int j = 0; j < n; ++j)
				delete E[i][j];//逐条删除
	}

	//顶点静态操作
	Tv& vertex(int v)   { return V[v].data; }	  //顶点v的 数据（该顶点的确存在）
	int inDegree(int v) { return V[v].inDegree; } //顶点v的 入度（该顶点的确存在）
	int outDegree(int v){ return V[v].outDegree; }//顶点v的 出度（该顶点的确存在）
	int firstNbr(int v) { return nextNbr(v, n); } //顶点i的首个邻接顶点
	int nextNbr(int v, int j){					  //已枚举至j，寻找下一邻接顶点
		while (-1 < j && !exists(v, --j));//逆序查找O(n)
		return j;
	}//顶点i的（相对于顶点j）下一邻接顶点(改用邻接表可提高效率,可提高至O(outDegree(i) + 1))
	VStatus& status(int v){ return V[v].status; }//顶点v的 状态
	int& dTime(int v)	{ return V[v].dTime; }   //顶点v的 时间标签dTime
	int& fTime(int v)   { return V[v].fTime; }   //顶点v的 时间标签fTime
	int& parent(int v)  { return V[v].parent; }  //顶点v在 遍历树中的父亲
	int& priority(int v){ return V[v].priority; }//顶点v在 遍历树中的优先级数

	//顶点动态操作
	int insert(Tv const &v);//插入 顶点v，返回编号
	Tv remove(int v);		//删除 顶点v及其关联边，返回该顶点信息

	//边的静态操作
	bool exists(int v, int u){ return (v < n) && (0 <= v) && (u < n) && (0 <= u)//短路求值
								&& E[v][u] != nullptr; }//边(v,u)是否存在
	EType& type(int v, int u){ return E[v][u]->type; }	//边(v,u)的 类型
	Te& edge(int v, int u)	 { return E[v][u]->data; }	//边(v,u)的 数据（该边的确存在）
	int& weight(int v, int u){ return E[v][u]->weight; }//边(v,u)的 权重

	//边的动态操作
	void insert(Te const&edge, int w, int v, int u);//在顶点v和u之间插入权重为w的边e
	Te remove(int v, int u);//删除顶点v和u之间的边e，返回该边信息
};

//顶点动态操作
template<typename Tv, typename Te>
int GraphMatrix<Tv,Te>::insert(Tv const &v)//插入顶点，返回编号
{
	for (int i = 0; i < n; ++i)//各顶点预留一条潜在的关联边
		E[i].insert(nullptr);
	++n;//顶点数增加
	E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*)nullptr));//创建新顶点对应的边向量
	return V.insert(Vertex<Tv>(v));//顶点向量增加一个顶点
}

template<typename Tv, typename Te>
Tv GraphMatrix<Tv, Te>::remove(int v)//删除顶点及其关联边，返回该顶点信息
{
	for (int j = 0; j < n; ++j)//所有出边
	{
		if (exists(v, j))//存在则逐条删除
		{
			delete E[v][j];
			--V[j].inDegree;//删除尾顶点的出边 即为 删除头顶点的入边
		}
	}
	E.remove(v); --n;//边集删除第v行
	Tv vData = vertex(v); V.remove(v);//向量集删除第v个顶点，并备份顶点信息
	for (int j = 0; j < n; ++j)//所有入边
	{
		if (Edge<Te> *e = E[j].remove(v))//若由V[j]指向V[v]的边存在
		{
			delete e;//则删除该边
			--V[j].outDegree;//该边为尾顶点的出边
		}
	}
	return vData;
}


//边的动态操作
template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::insert(Te const&edge, int w, int v, int u)//在顶点v和u之间插入权重为w的边e
{
	if (exists(v, u))return;//若边(v,u)已存在则直接结束
	E[v][u] = new Edge<Te>(edge, w);
	++e;//边的总数增加
	++V[v].outDegree;//尾顶点出度+1
	++V[u].inDegree; //头顶点入度+1
}

template<typename Tv, typename Te>
Te GraphMatrix<Tv, Te>::remove(int v, int u)//删除顶点v和u之间的边e，返回该边信息
{
	assert(exists(v, u));//若边(v,u)不存在则直接结束
	Te eData = edge(v, u);//记录被删除边信息
	delete E[v][u]; E[u][v] = nullptr;//删除边并使指针置空
	--e;//边的总数减少
	--V[v].outDegree;//尾顶点出度-1
	--V[u].inDegree; //头顶点入度-1
	return eData;//返回被删除边信息
}