#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

#include "word_count.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class BinarySearch {
private:
    vector<word_count> data;
    int length;
    int capacity;
    bool isSorted;

public:
    BinarySearch(int cap = 1000) : capacity(cap), length(0), isSorted(false) {
        data.reserve(capacity);
    }

    // 插入单词
    int inword(const string& word) {
        int comparisons = 0;
        
        // 如果已排序，使用二分查找查找是否存在
        if (isSorted) {
            int left = 0;
            int right = length - 1;
            
            while (left <= right) {
                comparisons++;
                int mid = left + (right - left) / 2;
                
                if (data[mid].get() == word) {
                    data[mid].numadd();
                    return comparisons;
                }
                
                if (data[mid].get() < word) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            
            // 如果不存在，需要插入并重新排序
            if (length < capacity) {
                data.push_back(word_count(word));
                length++;
                isSorted = false;  // 需要重新排序
                return comparisons;
            }
        } else {
            // 未排序时使用顺序查找
            for (int i = 0; i < length; i++) {
                comparisons++;
                if (data[i].get() == word) {
                    data[i].numadd();
                    return comparisons;
                }
            }
            
            // 如果不存在，添加到末尾
            if (length < capacity) {
                data.push_back(word_count(word));
                length++;
                return comparisons;
            }
        }
        
        return -1; // 容量已满
    }
    
    // 排序数据
    void sort() {
        if (!isSorted && length > 0) {
            std::sort(data.begin(), data.begin() + length, 
                [](const word_count& a, const word_count& b) {
                    return a.get() < b.get();
                });
            isSorted = true;
        }
    }
    
    // 二分查找
    int search(const string& word, int& comparisons) {
        comparisons = 0;
        
        // 确保数据已排序
        if (!isSorted) {
            sort();
        }
        
        int left = 0;
        int right = length - 1;
        
        while (left <= right) {
            comparisons++;
            int mid = left + (right - left) / 2;
            
            if (data[mid].get() == word) {
                return data[mid].getCount();
            }
            
            if (data[mid].get() < word) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;  // 未找到
    }
    
    // 获取所有单词(按字典序)
    string getall() {
        // 确保已排序
        if (!isSorted) {
            sort();
        }
        
        stringstream result;
        for (int i = 0; i < length; i++) {
            result << data[i].get() << " : " << data[i].getCount() << "\n";
        }
        return result.str();
    }
    
    // 返回大小
    int size() const {
        return length;
    }
};

#endif // BINARYSEARCH_H 