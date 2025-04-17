#ifndef SHUNXULIST_H
#define SHUNXULIST_H

#include "word_count.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class shunxulist {
private:
    vector<word_count> data;
    int length;
    int capacity;

    // 堆排序辅助函数
    void heapify(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && data[left].get() > data[largest].get())
            largest = left;

        if (right < n && data[right].get() > data[largest].get())
            largest = right;

        if (largest != i) {
            swap(data[i], data[largest]);
            heapify(n, largest);
        }
    }

public:
    shunxulist(int cap = 1000) : capacity(cap), length(0) {
        data.reserve(capacity);
    }

    // 堆排序
    void heapSort() {
        // 建立最大堆
        for (int i = length / 2 - 1; i >= 0; i--)
            heapify(length, i);

        // 逐个从堆中取出元素
        for (int i = length - 1; i > 0; i--) {
            swap(data[0], data[i]);
            heapify(i, 0);
        }
    }

    // 插入单词
    int inword(const string& word) {
        int comparisons = 0;
        
        // 顺序查找是否已存在
        for (int i = 0; i < length; i++) {
            comparisons++;
            if (data[i].get() == word) {
                data[i].numadd();
                return comparisons;
            }
        }
        
        // 不存在则添加
        if (length < capacity) {
            data.push_back(word_count(word));
            length++;
            return comparisons;
        }
        
        return -1; // 容量已满
    }
    
    // 获取所有单词(可能需要先排序)
    string getall() {
        // 按字母顺序排序
        sort(data.begin(), data.begin() + length, 
            [](const word_count& a, const word_count& b) {
                return a.get() < b.get();
            });
        
        stringstream result;
        for (int i = 0; i < length; i++) {
            result << data[i].get() << " : " << data[i].getCount() << "\n";
        }
        return result.str();
    }
    
    // 顺序查找
    int search(const string& word, int& comparisons) const {
        comparisons = 0;
        for (int i = 0; i < length; i++) {
            comparisons++;
            if (data[i].get() == word) {
                return data[i].getCount();
            }
        }
        return -1;
    }
    
    // 返回顺序表大小
    int size() const {
        return length;
    }
};

#endif // SHUNXULIST_H 