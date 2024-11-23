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
    testGraph();
    return 0;
}