#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <functional>
#include <chrono>
#include <cctype>
#include <iostream>

using namespace std;

class FileUtils {
public:
    // 从文件读取单词
    static vector<string> readWords(const string& filename) {
        vector<string> words;
        ifstream file(filename);
        string word;
        
        if (!file.is_open()) {
            throw runtime_error("Unable to open file: " + filename);
        }
        
        while (file >> word) {
            word = processWord(word);
            if (!word.empty()) {
                words.push_back(word);
            }
        }
        
        file.close();
        return words;
    }
    
    // 将结果写入文件
    static bool writeResults(const string& filename, const string& content) {
        ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        file << content;
        file.close();
        return true;
    }
    
    // 处理单词(过滤标点、转小写)
    static string processWord(const string& word) {
        string processed;
        for (char c : word) {
            if (isalpha(c)) {
                processed += tolower(c);
            }
        }
        return processed;
    }
    
    // 计时函数
    static double getExecutionTime(const function<void()>& func) {
        auto start = chrono::high_resolution_clock::now();
        func();
        auto end = chrono::high_resolution_clock::now();
        
        chrono::duration<double, milli> duration = end - start;
        return duration.count();
    }
};

#endif // FILEUTILS_H 