#pragma once
#include "CommonHeaders.h"

template <typename T>
class UndirectedGraph{

protected:
   unordered_map<T,unordered_set<T>> adjacencyList;
   
protected:
const unordered_map<T,unordered_set<T>>& getadjacencyList()const{
    return adjacencyList;
}
public:
    UndirectedGraph(){};
    ~UndirectedGraph(){};
    void addVertex(const T& vertex){
        if(adjacencyList.find(vertex)==adjacencyList.end()){
            adjacencyList[vertex]=unordered_set<T>();
        }

    }
    void addEdge(const T& u,const T& v){
        if(adjacencyList.find(u)==adjacencyList.end()){
            addVertex(u);
        }
        if(adjacencyList.find(v)==adjacencyList.end()){
            addVertex(v);
        }
        adjacencyList[u].insert(v);
        adjacencyList[v].insert(u);

    }
    void removeVertex(const T& vertex){
        if(adjacencyList.find(vertex)!=adjacencyList.end()){
            for(const T& neighbor:adjacencyList[vertex]){
                adjacencyList[neighbor].erase(vertex);
            }
            adjacencyList.erase(vertex);
        }
    }
    void removeEdge(const T& u,const T& v){
        if(adjacencyList.find(u)!=adjacencyList.end()&&adjacencyList.find(v)!=adjacencyList.end()){
            adjacencyList[u].erase(v);
            adjacencyList[v].erase(u);
        }
    }
    void display(){
        for(const pair<T,unordered_set<T>>& vertex:adjacencyList){
            cout<<vertex.first<<": ";
            for(const T& neighbor:vertex.second){
                cout<<neighbor<<" ";
            }
            cout<<endl;
        }
    }
    void findEdge(const T& u,const T& v){
        if(adjacencyList.find(u)!=adjacencyList.end()&&adjacencyList.find(v)!=adjacencyList.end())
        {
            if(adjacencyList[u].find(v)!=adjacencyList[u].end()){
                cout<<"edge "<<u<<" "<<v<<" is found"<<endl;
            }else{
                cout<<"edge "<<u<<" "<<v<<" is not found"<<endl;
            }
        }else{
            cout<<"vertex "<<u<<" or "<<v<<" is not found"<<endl;
        }
    }
    void findVertex(const T& vertex){
        if(adjacencyList.find(vertex)!=adjacencyList.end()){
            cout<<"vertex "<<vertex<<" is found"<<endl;
        }else{
            cout<<"vertex "<<vertex<<" is not found"<<endl;
        }
    }
    void dfs(const T& startVertex){
        unordered_set<T> visited;
        stack<T> stk;
        stk.push(startVertex);
        visited.insert(startVertex);
        while(!stk.empty()){
            T currentVertex=stk.top();
            stk.pop();
            cout<<currentVertex<<" ";
            for(const T& neighbor:adjacencyList[currentVertex]){
                if(visited.find(neighbor)==visited.end()){
                    stk.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
        cout<<"\n";
    }
    void bfs(const T& startVertex){
        unordered_set<T> visited;
        queue<T> q;
        q.push(startVertex);
        visited.insert(startVertex);
        while(!q.empty()){
            T currentVertex=q.front();
            q.pop();
            cout<<currentVertex<<" ";
            for(const T& neighbor:adjacencyList[currentVertex]){
                if(visited.find(neighbor)==visited.end()){
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
        cout<<"\n";
    }
    

};


// 带权无向图模板
template <typename T, typename WeightType>
class WeightedUndirectedGraph : public UndirectedGraph<T> {
private:
    unordered_map<T, unordered_map<T, WeightType>> edgeWeights; // 存储边的权重

public:
    WeightedUndirectedGraph() = default;
    ~WeightedUndirectedGraph() = default;

    // 重载添加边方法，添加权重
    void addEdge(const T& u, const T& v, const WeightType& weight) {
        // 调用基类的方法添加无权边
        UndirectedGraph<T>::addEdge(u, v);// 调用基类的公有方法添加无权边,不能直接使用基类的私有成员
        // 添加权重
        edgeWeights[u][v] = weight;
        edgeWeights[v][u] = weight; // 对称更新
    }
    // 获取边的权重
    WeightType getEdgeWeight(const T& u, const T& v) const {
        if (edgeWeights.find(u) != edgeWeights.end() && edgeWeights.at(u).find(v) != edgeWeights.at(u).end()) {
            return edgeWeights.at(u).at(v);
        } else {
            throw runtime_error("Edge does not exist");
        }
    }

  // 获取邻接顶点及权重
    const unordered_map<T, WeightType>& getNeighbors(const T& vertex) const {
        if (edgeWeights.find(vertex) != edgeWeights.end()) {
            return edgeWeights.at(vertex);
        } else {
            throw runtime_error("Vertex does not exist");
        }
    }

    // 检查顶点是否存在
    bool containsVertex(const T& vertex) const {
        return UndirectedGraph<T>::adjacencyList.find(vertex) != UndirectedGraph<T>::adjacencyList.end();
    }

    // Dijkstra 算法
    unordered_map<T, WeightType> dijkstra(const T& startVertex) {
        // 检查起始顶点是否存在
        if (!containsVertex(startVertex)) {
            throw runtime_error("Start vertex does not exist");
        }

        // 初始化数据结构
        unordered_map<T, WeightType> distances; // 记录起点到各顶点的最短距离
        unordered_map<T, T> previous;           // 记录路径
        auto compare = [](pair<T, WeightType>& a, pair<T, WeightType>& b) {
            return a.second > b.second; // 最小堆
        };
        priority_queue<pair<T, WeightType>, vector<pair<T, WeightType>>, decltype(compare)> minHeap(compare);

        // 初始化所有顶点的距离为正无穷
        for (const auto& vertex : UndirectedGraph<T>::adjacencyList) {
            distances[vertex.first] = numeric_limits<WeightType>::max();
        }

        // 起始顶点距离为 0
        distances[startVertex] = 0;
        minHeap.push({startVertex, 0});

        while (!minHeap.empty()) {
            T currentVertex = minHeap.top().first;
            WeightType currentDistance = minHeap.top().second;
            minHeap.pop();

            // 如果当前距离大于已记录的距离，跳过（已找到更短路径）
            if (currentDistance > distances[currentVertex]) {
                continue;
            }

            // 遍历邻接顶点
            try {
                const auto& neighbors = getNeighbors(currentVertex);
                for (const auto& neighbor : neighbors) {
                    T neighborVertex = neighbor.first;
                    WeightType weight = neighbor.second;
                    WeightType distanceThroughCurrent = currentDistance + weight;

                    // 如果找到更短路径，更新距离和前驱
                    if (distanceThroughCurrent < distances[neighborVertex]) {
                        distances[neighborVertex] = distanceThroughCurrent;
                        previous[neighborVertex] = currentVertex;
                        minHeap.push({neighborVertex, distanceThroughCurrent});
                    }
                }
            } catch (const runtime_error&) {
                // 无邻接顶点，跳过
                continue;
            }
        }

        // 可选：返回 previous，用于还原路径
        // return make_pair(distances, previous);

        return distances;
    }
    // 显示带权图
    void display() const {
        auto adjl=UndirectedGraph<T>::getadjacencyList();
        for (const auto& vertex :adjl) {
            cout << vertex.first << ": ";
            for (const auto& neighbor : vertex.second) {
                cout << "(" << neighbor << ", " << edgeWeights.at(vertex.first).at(neighbor) << ") ";
            }
            cout <<'\n';
        }
    }
};

void testGraph(){
    cout<<"test the undirected graph"<<endl;
    UndirectedGraph<int> ugph;
    ugph.addVertex(1);
    ugph.addVertex(2);
    ugph.addVertex(3);
    ugph.addVertex(4);
    ugph.addEdge(1,2);
    ugph.addEdge(2,3);
    ugph.findEdge(1,2);
    ugph.findEdge(1,3);
    ugph.findEdge(1,4);

    ugph.findVertex(1);
    cout<<"test the dfs and bfs of the undirected graph"<<endl;
    ugph.dfs(1);
    ugph.bfs(1);
    ugph.display();
    cout<<"\n\ntest the weighted undirected graph"<<endl;
    WeightedUndirectedGraph<int,int> wugph;
    wugph.addEdge(1,2,1);
    wugph.addEdge(2,3,2);
    wugph.addEdge(3,4,3);
    wugph.addEdge(4,1,4);
    wugph.findEdge(1,2);
    wugph.findEdge(1,3);
    wugph.findVertex(1);
    cout<<"test the dfs and bfs of the weighted undirected graph"<<endl;
    wugph.dfs(1);
    wugph.bfs(1);
    wugph.display();
}
void testdijkstra(){
    WeightedUndirectedGraph<string, double> graph;

    graph.addEdge("A", "B", 4);
    graph.addEdge("A", "C", 2);
    graph.addEdge("B", "C", 1);
    graph.addEdge("B", "D", 5);
    graph.addEdge("C", "D", 8);
    graph.addEdge("C", "E", 10);
    graph.addEdge("D", "E", 2);
    graph.addEdge("D", "F", 6);
    graph.addEdge("E", "F", 3);

    string startVertex = "A";
    auto distances = graph.dijkstra(startVertex);

    cout << "从顶点 " << startVertex << " 到其他顶点的最短距离：" << endl;
    for (const auto& pair : distances) {
        cout << "到顶点 " << pair.first << " 的距离为 " << pair.second << endl;
    }

}