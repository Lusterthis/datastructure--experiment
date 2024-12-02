#pragma once
#include"CommonHeaders.h"
#include"ll.h"
#include"tree.h"
#include"graph.h"
#include <nlohmann/json.hpp>
#include <curl/curl.h>

using json = nlohmann::json;

string ws2s(const std::wstring& wstr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        return conv.to_bytes(wstr);
    }
    
std::wstring s2ws(const std::string& str) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        return conv.from_bytes(str);
    }
    

class DeepSeekAPI {
public:
    DeepSeekAPI(const std::string& apiKey) : apiKey(apiKey) {}

    // 调用 DeepSeek API，获取 LLM 回复
    std::string callDeepSeekAPI(const std::string& jsonData) {
        CURL* curl = curl_easy_init();
        if (!curl) {
            // 处理错误
            fprintf(stderr, "curl_easy_init() failed\n");
            return "";
        }

        std::string responseStr;
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string authHeader = "Authorization: Bearer " + apiKey;
        headers = curl_slist_append(headers, authHeader.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "http://8.134.223.251:3000/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonData.size());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStr);

        // 忽略 SSL 证书验证（如果使用 HTTPS）
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            // 处理错误
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // 清理资源
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return responseStr;
    }

private:
    std::string apiKey;

    // 用于接收响应数据的回调函数
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        size_t totalSize = size * nmemb;
        std::string* responseStr = (std::string*)userp;
        responseStr->append((char*)contents, totalSize);
        return totalSize;
    }
};
//=============================================
using DialoguePair = std::pair<std::wstring, std::wstring>;

class DialogueHistory {
public:
    // 添加一条对话记录
    void addRecord(const std::wstring& userInput, const std::wstring& llmResponse) {
        history.Insert({userInput, llmResponse});
    }

    // 获取对话历史
    const SingleLinkedList<DialoguePair>& getHistory() const {
        return history;
    }

    // 显示对话历史
    void displayHistory() const {
        for (auto entry  =history.head; entry!=NULL;entry=entry->next) {
            std::wcout << L"用户: " << entry->value.first << std::endl;
            std::wcout << L"助手: " << entry->value.second << std::endl;
            std::wcout << L"------------------------" << std::endl;
        }
    }

private:
    SingleLinkedList<DialoguePair> history;
};
//================================================================


class DialogueTreeManager {
public:
    DialogueTreeManager() {
        dialogueTree = new BinarySearchTree<DialogueData>();
    }

    ~DialogueTreeManager() {
        delete dialogueTree;
    }

    // 设置系统提示词
    void setSystemPrompt(const std::wstring& prompt) {
        systemPrompt = prompt;
    }

    // 添加对话节点
    void addDialogueNode(const std::wstring& userInput, const std::wstring& llmResponse) {
        DialogueData data = {userInput, llmResponse};
        dialogueTree->insert(data);
    }

    // 获取并显示对话历史
    void getDialogueHistory() {
        dialogueTree->inOrderTraversal();
    }

private:
    BinarySearchTree<DialogueData>* dialogueTree;
    std::wstring systemPrompt;
};
//====================================================================


class DialogueManager {
public:
    DialogueManager(const std::string& apiKey) : deepSeekAPI(apiKey) {
        dialogueTreeManager = new DialogueTreeManager();
    }

    ~DialogueManager() {
        delete dialogueTreeManager;
    }

    // 设置系统提示词
    void setSystemPrompt(const std::wstring& prompt) {
        dialogueTreeManager->setSystemPrompt(prompt);
    }

    // 处理用户输入
   void processUserInput(const std::wstring& userInput) {
    // 构建消息列表
    nlohmann::json messages = nlohmann::json::array();
    if (!systemPrompt.empty()) {
        messages.push_back({{"role", "system"}, {"content", ws2s(systemPrompt)}});
    }

    // 获取对话历史
    const SingleLinkedList<DialoguePair>& history = dialogueHistory.getHistory();
    for (auto entry = history.head; entry != nullptr; entry = entry->next) {
        messages.push_back({{"role", "user"}, {"content", ws2s(entry->value.first)}});
        messages.push_back({{"role", "assistant"}, {"content", ws2s(entry->value.second)}});
    }

    // 添加当前用户输入
    messages.push_back({{"role", "user"}, {"content", ws2s(userInput)}});

    // 构建请求数据
    nlohmann::json requestData = {
        {"model", "deepseek-chat"},
        {"messages", messages},
        {"max_tokens", 150},
        {"temperature", 0.7}
    };

    // 调用 DeepSeek API
    std::string llmResponseStr = deepSeekAPI.callDeepSeekAPI(requestData.dump());

    // 输出 API 响应
    std::cout << "API 响应：" << llmResponseStr << std::endl;

    // 解析 LLM 回复
    nlohmann::json responseJson = nlohmann::json::parse(llmResponseStr);

    // 检查是否有错误
    if (responseJson.contains("error")) {
        std::string errorMsg = responseJson["error"]["message"];
        std::cerr << "API 错误：" << errorMsg << std::endl;
        return;
    }

    // 检查并获取回复内容
    std::string llmReply;
    if (responseJson.contains("choices") && !responseJson["choices"].is_null()) {
        auto choices = responseJson["choices"];
        if (!choices.empty()) {
            auto message = choices[0]["message"];
            llmReply = message.value("content", "");
        }
    }

    if (llmReply.empty()) {
        std::wcout << L"抱歉，未能获得有效的回复。" << std::endl;
    } else {
        std::wstring llmResponse = s2ws(llmReply);
        // 更新对话记录和上下文
        dialogueHistory.addRecord(userInput, llmResponse);
        dialogueTreeManager->addDialogueNode(userInput, llmResponse);

        // 输出回复
        std::wcout << L"智能助手: " << llmResponse << std::endl;
    }
}

    // 显示对话历史
    void displayDialogueHistory() const {
        dialogueHistory.displayHistory();
    }
    

private:
    DialogueHistory dialogueHistory;
    DialogueTreeManager* dialogueTreeManager;
    std::wstring systemPrompt;
    DeepSeekAPI deepSeekAPI;

    // 工具函数
    // std::string ws2s(const std::wstring& wstr);
    // std::wstring s2ws(const std::string& str);
};
//=====================================================================
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

