# Week1 - 抽象与封装

本周我们需要实现两个类：

- `Edge`：有向边
- `Graph`：有向无权图

你不能修改给定的接口，但可以随意决定类的内部实现（类有哪些数据成员、类有哪些其他的接口、这些接口都是怎么实现的等等）。评测时，会使用默认的配置文件进行编译。

## `Edge`

`Edge`类表示有向边，它具有构造函数、析构函数和两个接口：

- `Edge(int source, int destination)`：构造一条起点为`source`、终点为`destination`的边对象
- `~Edge()`：销毁这条边
- `int GetSource() const`：获取起点编号
- `int GetDestination() const`：获取终点编号

注释：

1. C++运行时在创建新的对象时会首先在内存中分配空间，然后调用类的**构造函数**，用于初始化成员并申请资源（如文件、锁、动态对象等）；当对象的生命周期结束，删除对象时会调用**析构函数**，用于归还资源。
2. 两个接口声明中的`const`表示这个成员函数是**常函数**，常函数不可以对类成员属性的值进行修改（否则会在编译时抛出错误）。
3. 你是否很好奇为什么不直接用`struct`或者将边的两个端点声明成`public`成员变量？有这个疑问就对了！从现在来看，这个设计完全就是在滥用面向对象编程（OOP可以导致代码过于臃肿降低开发效率）；但是到下一周我们就会利用这个特性。

用例：

```c++
Edge e(1, 2); // 创建一条1指向2的有向边
assert(e.GetSource() == 1);
assert(e.GetDestination() == 2);
```

## `Graph`

`Graph`类表示有向无权图，它具有构造函数、析构函数和十四个接口：

- `Graph()`：构造一个新的图
- `~Graph()`：销毁这张图
- `bool AddVertex(int vertex)`：添加一个指定编号的点，如果添加成功返回`true`，如果点已经存在返回`false`
- `bool RemoveVertex(int vertex)`：删除指定编号的点，如果删除成功返回`true`，如果点不存在返回`false`
- `bool AddEdge(int vertex1, int vertex2)`：添加一条`v1`指向`v2`的有向边，如果添加成功返回`true`，如果点不存在或者边已经存在返回`false`
- `bool RemoveEdge(int vertex1, int vertex2)`：删除`v1`指向`v2`的有向边，如果删除成功返回`true`，如果点不存在或者边不存在返回`false`
- `int CountVertices() const`：返回点的数量
- `int CountEdges() const`：返回边的数量
- `bool ContainsVertex(int vertex) const`：判断指定编号的点是否存在
- `bool ContainsEdge(int vertex1, int vertex2) const`：判断`v1`指向`v2`的边是否存在
- `std::vector<int> GetVertices() const`：获取图中所有点的列表
- `std::vector<Edge> GetEdges() const`：获取图中所有边的列表
- `std::vector<Edge> GetIncomingEdges(int vertex) const`：获取某个点的入边列表，如果点不存在返回空列表
- `std::vector<Edge> GetOutgoingEdges(int vertex) const`：获取某个点的出边列表，如果点不存在返回空列表
- `int GetDegree(int vertex) const`：返回指定编号的点的度（有向图的度就是出度），如果点不存在返回0
- `std::vector<int> GetNeighbors(int vertex) const`：获取某个点的邻居列表（有向图的邻居就是出边指向的点），如果点不存在返回空列表

注释：

- 有向无权图不允许出现重边，可能存在环、自环；
- 添加点的编号未必是连续的，可能是`1`，可能是`2147483647`，需要自行处理；
- 所有的`std::vector`都可以以**任意顺序**排列其中的元素，但不允许出现重复元素；
- 图的内部采用邻接表或邻接矩阵存储都可以，时间复杂度的要求非常松，点的数量不会超过1000；
- 提示：接口的实现过程中会出现大量的重复操作，可以添加子接口，非常不建议copy-paste。

用例：

```c++
Graph g; // 创建一张新的图

assert(g.AddVertice(1) == true);
assert(g.AddVertice(2) == true);
assert(g.AddVertice(3) == true);
assert(g.AddVertice(3) == false); // 3号点已经存在了
assert(g.AddVertice(4) == true);
assert(g.ContainsVertex(4) == true);
assert(g.RemoveVertice(4) == true);
assert(g.ContainsVertex(4) == false);
assert(g.RemoveVertice(5) == false);

assert(g.AddEdge(1, 2) == true);
assert(g.AddEdge(1, 3) == true);
assert(g.AddEdge(2, 5) == false); // 5号点不存在
assert(g.ContainsEdge(1, 2) == true);
assert(g.ContainsEdge(2, 5) == false);

assert(g.GetVertices().size() == g.CountVertices()); // 4
assert(g.GetEdges().size() == 2);
assert(g.GetIncomingEdges(1).size() == 0);
assert(g.GetOutgoingEdges(1).size() == 2); // {{1, 2}, {1, 3}}
assert(g.GetDegree(1) == 2);
assert(g.GetNeighbors(1).size() == 2); // {2, 3}
assert(g.GetNeighbors(2).size() == 0);
```