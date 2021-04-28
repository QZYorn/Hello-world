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
		{
			if (status(u) == UNDISCOVERED)//若邻接顶点处于“未发现”的状态即未入队
			{
				Q.enqueue(u);//则将u邻接顶点入队
				status(u) = DISCOVERED;//并将u置为“已发现”
				status(v, u) = TREE;//关联边(v,u)引入作为“树边”
				parent(u) = v;//u在树中的父节点为v
			}
			else//若邻接顶点为“已发现”即已入队 或 为“已访问”即已出队
				status(v, u) = CROSS;//将(v,u)归类为“跨边”
		}//v的所有邻接顶点访问完毕
		status(v) = VISITED;//至此，当前顶点访问完毕，v状态置为“已访问”
	}//最终形成一支遍历支撑树
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock)//(连通域)深度优先搜索算法
{
	status(v) = DISCOVERED;//v顶点状态置为“已发现”
	dTime(v) = ++clock;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))//枚举v的所有邻接顶点
	{
		switch (status(u))
		{
		case UNDISCOVERED://“未发现”
			status(v, u) = TREE; //(v,u)边引入作为“树边”
			parent(u) = v;		 //支撑树中u父亲指向v
			DFS(u, clock);		 //以u为首顶点递归调用DFS
			break;
		case DISCOVERED:  //“已发现”，但尚未访问完毕，则此顶点应属被后代指向的祖先
			status(v, u) = BACKWARD;//(v,u)边状态置为“后向边”，即“回边”，后代指向祖先
			break;
		default:		  //“已访问”，则依据v,u访问的次序，将(v,u)状态置为“前向边”或“跨边”
			status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;//“前向边”祖先指向后代，“跨边”无直属关系的不同分支
			break;
		}
	}
	status(v) = VISITED;//v顶点状态置为“已访问”
	fTime(v) = ++clock;

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int, int&, Stack<int>&)//(连通域)基于DFS的双连通分量分解算法
{

}

template<typename Tv, typename Te>
bool Graph<Tv, Te>::Tsort(int v, int &clock, Stack<Tv> *S)//(连通域)基于DFS的拓扑排序算法
{
	//精简版
	status(v) = DISCOVERED;//初始化
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
	{
		if (status(u) == UNDISCOVERED)
		{
			parent(u) = v;
			if (!Tsort(u, clock, S))//若从u出发的拓扑排序不存在
				return false;//则整个图的拓扑排序都不存在
			break;
		}
		else if (status(u) == DISCOVERED)
		{
			return false;
			break;
		}
	}
	status(v) = VISITED;
	S->push(vertex(v));//v顶点访问完毕时才将其数据推入栈中
	return true;//v及其后台皆可拓扑排序
}

template<typename Tv, typename Te>
template<typename PU> void Graph<Tv, Te>::PFS(int, PU)//(连通域)优先级搜索框架
{

}

//算法
template<typename Tv,typename Te>
void Graph<Tv, Te>::bfs(int s)//广度优先搜索算法
{
	reset(); int clock = 0; int v = s;//初始化
	do//逐一检查各顶点
	{
		if (UNDISCOVERED == status(v))//若顶点状态为“未发现”
			BFS(v, clock);//则从该顶点出发进行一次广度优先遍历
	} while (s != v = ( ++v % n));//按序号检查，故不漏不重
	//从s顶点出发，向后依次遍历至n，再回头到0开始遍历,再到s-1。故无论起始于何处都能遍历完全
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int)//深度优先搜索算法
{
	reset(); int clock = 0; int v = s;//初始化
	do//逐一检查各顶点
	{
		if (UNDISCOVERED == status(v))//若顶点状态为“未发现”
			DFS(v, clock);//则从该顶点出发进行一次广度优先遍历
	} while (s != v = (++v % n));//按序号检查，故不漏不重
	//从s顶点出发，向后依次遍历至n，再回头到0开始遍历,再到s-1。故无论起始于何处都能遍历完全
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int)//基于DFS的双连通分量分解算法
{

}

template<typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s)//基于DFS的拓扑排序算法
{
	reset(); int clock = 0; int v = s;
	Stack<Tv>* S = new Stack<Tv>;
	do
	{
		if (status(v) == UNDISCOVERED)//从“未发现”的顶点转入
			if (!Tsort(v, clock, S))//若v所在连通域不为DAG
			{
				while (!S->empty())//则将栈清空
					S->pop();
				break;//然后直接结束全图遍历
			}
	} while (s != v = (++v % n));
	return S;//若为DAG则S内各顶点自顶向底排列;否则（非DAG，不存在拓扑排序）S为空
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