#pragma once
#include"CommonHeaders.h"


void removeDuplicates(vector<string>& data)
 {
    unordered_set<string> seen;
    auto it = data.begin();
    while (it != data.end()) {
        if (seen.find(*it) != seen.end()) {
            auto tmp=it;
            ++it;
            data.erase(tmp); // 删除重复项
            
        } else {
            seen.insert(*it);
            ++it;
        }
    }
}
// 去除停用词
void removeStopWords(std::vector<std::string>& data, const std::vector<std::string>& stopWords) {
    for (auto& line : data) {
        for (const auto& stopWord : stopWords) {
            size_t pos = 0;
            // 使用循环查找并删除所有出现的停用词
            while ((pos = line.find(stopWord, pos)) != std::string::npos) {
                line.erase(pos, stopWord.length());
                // 删除后，pos不增加，因为后面的字符已经前移
            }
        }
    }
}
// 去除无效字符

void cleanInvalidCharacters(vector<string>& data) {
    for (auto& line : data) {
        string cleanedLine;
        for (char ch : line) {
            if (isalnum(static_cast<unsigned char>(ch)) || isspace(static_cast<unsigned char>(ch)) || (ch >= 0x80)) {
                cleanedLine += ch;
            }
        }
        line = cleanedLine;
    }
}

// 数据查找功能
void searchInArray(const vector<string>& data, const string& keyword) {
    cout << "\n包含关键词 \"" << keyword << "\" 的句子有：" << endl;
    for (const auto& line : data) {
        if (line.find(keyword) != string::npos) {
            cout << line << endl;
        }
    }
}

void cleanData(vector<string>& data, const vector<string>& stopWords) {
   
    // 去除重复的句子
    removeDuplicates(data);
    cout << "\n去重后的数据: " << endl;
    for (const auto& line : data) {
        cout << line << endl;
    }

    // 去除停用词
    removeStopWords(data, stopWords);
    cout << "\n去除停用词后的数据: " << endl;
    for (const auto& line : data) {
        cout << line << endl;
    }

    // 去除无效字符
    cleanInvalidCharacters(data);
    cout << "\n去除非ASCII字符后的数据: " << endl;
    for (const auto& line : data) {
        cout << line << endl;
    }
}
std::vector<std::string> searchInLL(const std::vector<std::string>& data, const std::string& keyword) {
    std::vector<std::string> results;
    for (const auto& sentence : data) {
        if (sentence.find(keyword) != std::string::npos) {
            results.push_back(sentence);
        }
    }
    return results;
}
