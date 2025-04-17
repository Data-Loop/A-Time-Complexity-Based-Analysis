#ifndef WORD_COUNT_H
#define WORD_COUNT_H

#include <string>
using namespace std;

class word_count {
private:
    string word;
    int count;

public:
    // 构造函数
    word_count(const string& w = "") : word(w), count(1) {}
    
    // 获取单词
    string get() const { return word; }
    
    // 设置单词并重置计数
    void setcount(const string& w) {
        word = w;
        count = 1;
    }
    
    // 获取词频
    int getCount() const { return count; }
    
    // 增加词频
    void numadd() { count++; }
    
    // 重载比较运算符
    bool operator<(const word_count& other) const {
        return word < other.word;
    }
    
    bool operator==(const word_count& other) const {
        return word == other.word;
    }
};

#endif // WORD_COUNT_H 