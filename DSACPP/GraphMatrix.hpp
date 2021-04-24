#pragma once
#include"Vector.hpp"
#include"Graph.hpp"


template<typename Tv>//顶点对象
struct Vertex		
{
	Tv data; int inDegree, outDegree; VStatus status;//数据域，入度，出度，状态
	int dTime, fTme;//时间标签
	int parent; int priority;//在遍历树中的父节点、优先级数
	Vertex(Tv const &tv = (Tv)0) ://构造新顶点
		data(tv), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};


template<typename Te>//边对象
struct Edge			
{
	Te data; int weight; EType type;//数据域，权重，类型
	Edge(Te const&te, int w) ://构造新边
		data(te), weight(w), type(UNDETERMINED){}
};




template<typename Tv, typename Te>//邻接矩阵
class GraphMatrix :public Graph<Tv, Te>
{
private:
	Vector<Vertex<Tv>> V;		  //顶点集
	Vector < Vector<Edge<Te>*>> E;//边集(邻接矩阵)
public:
	Tv& vertex(int v){return V[v]}	  //顶点v的 数据（该顶点的确存在）
	int inDegree(int v) = 0;	  //顶点v的 入度（该顶点的确存在）
	int outDegree(int v) = 0;	  //顶点v的 出度（该顶点的确存在）
	int firstNbr(int v){ return nextNbr(v, n); }	  //顶点i的首个邻接顶点
	int nextNbr (int v, int j);//顶点i的（相对于顶点j）下一邻接顶点(改用邻接表可提高效率)
	VStatus& status(int v) = 0; //顶点v的 状态
	int& dTime(int v) = 0;	  //顶点v的 时间标签dTime
	int& fTime(int v) = 0;      //顶点v的 时间标签fTime
	int& parent(int v) = 0;     //顶点v在 遍历树中的父亲
	int& priority(int v) = 0;   //顶点v在 遍历树中得优先级数
};


template<typename Tv, typename Te>
int GraphMatrix<Tv, Te>::nextNbr(int v, int j)//已枚举至j，寻找下一邻接顶点
{
	while (-1 < j && !exists(v, --j));//逆序查找O(n)
	return j;
	
}//改用邻接表可提高至O(outDegree(i) + 1)