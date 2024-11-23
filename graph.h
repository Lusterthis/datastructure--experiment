#pragma once
#include "CommonHeaders.h"

template <typename T>
class UndirectedGraph{

private:
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

    // 显示带权图
    void display() const {
        auto adjl=UndirectedGraph<T>::getadjacencyList();
        for (const auto& vertex :adjl) {
            cout << vertex.first << ": ";
            for (const auto& neighbor : vertex.second) {
                cout << "(" << neighbor << ", " << edgeWeights.at(vertex.first).at(neighbor) << ") ";
            }
            cout << endl;
        }
    }
};

void testGraph(){
    cout<<"test the undirected graph"<<endl;
    UndirectedGraph<int> ugph;
    ugph.addVertex(1);
    ugph.addVertex(2);
    ugph.addVertex(3);
    ugph.addEdge(1,2);
    ugph.addEdge(2,3);
    ugph.findEdge(1,2);
    ugph.findEdge(1,3);
    ugph.findVertex(1);
    ugph.display();
    cout<<"\n\ntest the weighted undirected graph"<<endl;
    WeightedUndirectedGraph<int,int> wugph;
    wugph.addEdge(1,2,1);
    wugph.addEdge(2,3,2);
    wugph.findEdge(1,2);
    wugph.findEdge(1,3);
    wugph.findVertex(1);
    wugph.display();
}