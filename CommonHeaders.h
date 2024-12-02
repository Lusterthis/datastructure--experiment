// CommonHeaders.h

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<unordered_set>
#include<algorithm>
#include<set>
#include<sstream>
#include<bits/stdc++.h>



using namespace std;
// 根据需要添加更多头文件
struct DialogueData {
    std::wstring userInput;       // 用户输入
    std::wstring llmResponse;     // LLM 回复

    // 重载小于运算符，以便在二叉搜索树中进行比较
    bool operator<(const DialogueData& other) const {
        return userInput < other.userInput;
    }
};