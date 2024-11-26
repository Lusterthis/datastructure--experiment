#include"CommonHeaders.h"
#include"ll.h"
#include"llm.h"
#include"tree.h"
#include"graph.h"


Array<string> an_arr(0);
void loadData(const string& filename) { 
    ifstream file(filename); // 打开文件流
    if (!file.is_open()) {
    cerr << "无法打开文件：" << filename << endl;
    return;
}
    string line;
    
    
    while (getline(file, line)) { // 逐行读取文件内容
        an_arr.Insert(line,an_arr.getSize()); // 将每一行插入到链表中
    }
}



int main()
{
    // testGraph();
    // testdijkstra();
    cout<<"=====knowledgegraph testing====="<<endl;
    WeightedUndirectedGraph<string,int> knowledgegraph;
    knowledgegraph.addVertex("C++");
    knowledgegraph.addVertex("Java");
    knowledgegraph.addVertex("Computer Science");
    knowledgegraph.addVertex("Data Structure");
    knowledgegraph.addVertex("Operating System");
    knowledgegraph.addVertex("Computer Network");
    knowledgegraph.addVertex("Discrete Math");
    knowledgegraph.addVertex("Industrial Engineering");
    knowledgegraph.addEdge("C++","Java",1);
    knowledgegraph.addEdge("Operating System","Computer Science",1);
    knowledgegraph.addEdge("Computer Network","Computer Science",1);
    knowledgegraph.addEdge("Data Structure","C++",1);
    knowledgegraph.addEdge("Data Structure","Java",1);
    knowledgegraph.addEdge("Discrete Math","Computer Science",1);
    knowledgegraph.addEdge("Discrete Math","Industrial Engineering",1);
    knowledgegraph.display();
   cout<<"find the edge between C++ and Java,and the weight is 1"<<endl;
    knowledgegraph.findEdge("C++","Java");
    knowledgegraph.findEdge("C++","Operating System");
 cout<<"test the dfs and bfs of the knowledge graph"<<endl;
    knowledgegraph.dfs("C++");
    knowledgegraph.bfs("C++");
    return 0;
}