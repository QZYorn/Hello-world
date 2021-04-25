#pragma once
#include"Queue.hpp"
typedef enum{ UNDISCOVERED, DISCOVERED, VISITED }VStatus;//顶点状态
typedef enum{ UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD }EType;//边在遍历树中所属的状态

template<typename Tv, typename Te>
class Graph//图Graph抽象模板类
{
private:
	void reset()//所有顶点、边的辅助信息复位
	{
		for (int i = 0; i < n; ++i)
		{
			status(i) = UNDISCOVERED; dTime(i) = fTime(i) = -1; //状态、时间标签 复位
			parent(i) = -1; priority(i) = INT_MAX;//(在遍历树中)父节点、优先级数 复位
			for (int j = 0; j < n; ++j)//所有边的
				if (exists(i, j))
					type(i, j) = UNDETERMINED;//类型 复位
		}
	}
	//算法
	void BFS(int, int&);					//(连通域)广度优先搜索算法
	void DFS(int, int&);					//(连通域)深度优先搜索算法
	void BCC(int, int&, Stack<int>&);		//(连通域)基于DFS的双连通分量分解算法
	bool Tsort(int, int&, Stack<Tv>*);		//(连通域)基于DFS的拓扑排序算法
	template<typename PU> void PFS(int, PU);//(连通域)优先级搜索框架
public:
	virtual ~Graph(){}

	//顶点
	int n;//顶点总数
	virtual int insert(Tv const&) = 0;  //插入顶点，返回编号
	virtual Tv remove(int) = 0;		    //删除顶点及其关联边，返回该顶点信息
	virtual Tv& vertex(int) = 0;	  //顶点v的 数据（该顶点的确存在）
	virtual int inDegree(int) = 0;	  //顶点v的 入度（该顶点的确存在）
	virtual int outDegree(int) = 0;	  //顶点v的 出度（该顶点的确存在）
	virtual int firstNbr(int) = 0;	  //顶点v的 首个邻接顶点
	virtual int nextNbr(int, int) = 0;//顶点v的（相对于顶点j）下一邻接顶点
	virtual VStatus& status(int) = 0; //顶点v的 状态
	virtual int& dTime(int) = 0;	  //顶点v的 时间标签dTime
	virtual int& fTime(int) = 0;      //顶点v的 时间标签fTime
	virtual int& parent(int) = 0;     //顶点v在 遍历树中的父亲
	virtual int& priority(int) = 0;   //顶点v在 遍历树中得优先级数


	//边:这里约定，无向边统一转化为方向互逆的一对 有向边，从而将 无向图视为 有向图的特例
	int e;//边的总数
	virtual bool exists(int, int) = 0;//边(v,u)是否存在
	virtual void insert(Te const&, int, int, int) = 0;//在顶点v和u之间插入权重为w的边e
	virtual Te remove(int, int) = 0;  //删除顶点v和u之间的边e，返回该边信息
	virtual EType& type(int, int) = 0;	//边(v,u)的 类型
	virtual Te& edge(int, int) = 0;		//边(v,u)的 数据（该边的确存在）
	virtual int& weight(int, int) = 0;	//边(v,u)的 权重

	//算法
	void bfs(int);//广度优先搜索算法
	void dfs(int);//深度优先搜索算法
	void bcc(int);		  //基于DFS的双连通分量分解算法
	Stack<Tv>* tSort(int);//基于DFS的拓扑排序算法
	void prim(int);	   //最小支撑树Prim的算法
	void dijkstra(int);//最短路径Dijkstra算法
	template<typename PU> void pfs(int, PU);//优先级搜索框架

};
//算法
template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock)//(连通域)广度优先搜索算法
{
	Queue<int> Q; Q.enqueue(v);//创建队列Q并使v入队
	status(v) = DISCOVERED;//v状态置为“已发现”
	while (!Q.empty())//Q队列清空前不断循环
	{
		int v = Q.dequeue();//队首出队
		dTime(v) = ++clock;//更新时间标签dTime
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))//初始化需访问顶点u为首邻接顶点，直到u越界，每次迭代u转为下一邻接顶点
			/*

			*/
			;
		status(v) = VISITED;//至此，当前顶点访问完毕，v状态置为“已访问”
	}
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int, int&)//(连通域)深度优先搜索算法
{

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int, int&, Stack<int>&)//(连通域)基于DFS的双连通分量分解算法
{

}

template<typename Tv, typename Te>
bool Graph<Tv, Te>::Tsort(int, int&, Stack<Tv>*)//(连通域)基于DFS的拓扑排序算法
{

}

template<typename Tv, typename Te>
template<typename PU> void Graph<Tv, Te>::PFS(int, PU)//(连通域)优先级搜索框架
{

}

//算法
template<typename Tv,typename Te>
void Graph<Tv, Te>::bfs(int)//广度优先搜索算法
{
	
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int)//深度优先搜索算法
{

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int)//基于DFS的双连通分量分解算法
{

}

template<typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int)//基于DFS的拓扑排序算法
{

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int)//最小支撑树Prim的算法
{

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int)//最短路径Dijkstra算法
{

}

template<typename Tv, typename Te>
template<typename PU> void Graph<Tv, Te>::pfs(int, PU)//优先级搜索框架
{

}