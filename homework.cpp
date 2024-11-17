#include"CommonHeaders.h"
#include"ll.h"
#include"llm.h"


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
    //system("chcp 65001");
    //testArray();
    //testSingleLinkedList();
    //testDoubleLinkedList();
    loadData("test.txt");
    
    cout << "原始数据: " << endl;
    for (int i=0;i<an_arr.getSize();++i) {
        cout <<an_arr[i] << endl;
    }
    vector<string> stopWords = {"是", "了", "的", "了","哉","一","app","std::"};
    cleanData(an_arr.getarr(),stopWords);
    cout<<"寻找包含关键词的句子"<<endl;
    auto ans=searchInLL(an_arr.getarr(),"1");
    for(auto &i:ans){
        cout<<i<<endl;
    }


    return 0;
}