#include"CommonHeaders.h"

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
    //test:
//     CURL *curl;
//     CURLcode res;
//     curl = curl_easy_init();
//     if (curl) {curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
//     res = curl_easy_perform(curl);if (res != CURLE_OK) {fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//     }curl_easy_cleanup(curl);
// }

//     json jsonData;
//     jsonData["name"] = "John Doe";
//     jsonData["age"] = 30;
//     std::string jsonString = jsonData.dump();
//     std::cout << jsonString << std::endl;

    setlocale(LC_ALL, "");
    // CURL *curl = curl_easy_init();
    // if(curl) {
    //     // 设置请求的 URL
    //     curl_easy_setopt(curl, CURLOPT_URL, "http://8.134.223.251:3000/v1/chat/completions");

    //     // 设置请求头
    //     struct curl_slist *headers = NULL;
    //     headers = curl_slist_append(headers, "Content-Type: application/json");
    //     std::string apiKey = "<sk-DaCIQAg1zhTVlO6d2a8bA9Bc18E1431184Bc9cE3Bb1cAdAa>";
    //     std::string authHeader = "Authorization: Bearer " + apiKey;
    //     headers = curl_slist_append(headers, authHeader.c_str());
    //     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    //     // 设置请求方法为 POST
    //     curl_easy_setopt(curl, CURLOPT_POST, 1L);

    //     // 设置请求体
    //     const char* jsonData = R"({
    //         "model": "deepseek-chat",
    //         "messages": [
    //             {
    //                 "role": "system",
    //                 "content": "你是一个数据结构小助手"
    //             },
    //             {
    //                 "role": "user",
    //                 "content": "你能帮我写一个冒泡排序吗？"
    //             }
    //         ],
    //         "max_tokens": 150,
    //         "temperature": 0.7
    //     })";
    //     curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData);

    //     // 执行请求
    //     CURLcode res = curl_easy_perform(curl);
    //     if(res != CURLE_OK) {
    //         fprintf(stderr, "请求失败: %s\n", curl_easy_strerror(res));
    //     }

    //     // 清理
    //     curl_slist_free_all(headers);
    //     curl_easy_cleanup(curl);
    // }

    const std::string apiKey = "sk-DaCIQAg1zhTVlO6d2a8bA9Bc18E1431184Bc9cE3Bb1cAdAa"; 
    DialogueManager dialogueManager(apiKey);
    std::wstring systemPrompt = L"您是一个智能助手，能够回答用户的各种问题。";
    dialogueManager.setSystemPrompt(systemPrompt);
        std::wstring userInput;
    while (true) {
        std::wcout << L"用户: ";
        std::getline(std::wcin, userInput);

        // 检查退出条件
        if (userInput == L"退出" || userInput == L"exit") {
            break;
        }

        // 处理用户输入
        dialogueManager.processUserInput(userInput);
    }
    return 0;
}