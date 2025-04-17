#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "word_count.h"
#include <vector>
#include <string>
#include <sstream>

class HashTable {
private:
    static const int TABLE_SIZE = 10007;  // 质数表大小
    vector<word_count> table;
    int count;
    
    // DJB2哈希函数
    int hash(const string& word) const {
        unsigned long hash = 5381;
        for (char c : word) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % TABLE_SIZE;
    }
    
    // 二次探测
    int quadraticProbe(int hash, int i) const {
        return (hash + i * i) % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE), count(0) {}
    
    // 插入单词
    int inword(const string& word) {
        if (count >= TABLE_SIZE * 0.75) return -1;  // 负载因子超过0.75时不再插入

        int hashValue = hash(word);
        int i = 0;
        int pos;

        do {
            pos = quadraticProbe(hashValue, i);
            
            if (table[pos].get().empty()) {
                table[pos].setcount(word);
                count++;
                return i + 1;
            }
            
            if (table[pos].get() == word) {
                table[pos].numadd();
                return i + 1;
            }
            
            i++;
        } while (i < TABLE_SIZE);

        return -1;
    }
    
    // 获取所有单词
    string getall() const {
        stringstream result;
        for (const auto& item : table) {
            if (!item.get().empty()) {
                result << item.get() << " : " << item.getCount() << "\n";
            }
        }
        return result.str();
    }
    
    // 查找单词
    int search(const string& word, int& comparisons) const {
        comparisons = 0;
        int hashValue = hash(word);
        int i = 0;
        int pos;

        do {
            comparisons++;
            pos = quadraticProbe(hashValue, i);
            
            if (table[pos].get() == word) {
                return table[pos].getCount();
            }
            
            if (table[pos].get().empty()) {
                return -1;
            }
            
            i++;
        } while (i < TABLE_SIZE);

        return -1;
    }
};

#endif // HASHTABLE_H 