#include <iostream>
#include <string>
#include <iomanip>
#include "word_count.h"
#include "shunxulist.h"
#include "linklist.h"
#include "binarySearch.h"
#include "BSTree.h"
#include "HashTable.h"
#include "FileUtils.h"

using namespace std;

// 顺序表顺序查找测试
void testSequentialSearch() {
    cout << "\n=== 顺序表顺序查找测试 ===" << endl;
    shunxulist list(10000);
    auto words = FileUtils::readWords("InFile.txt");
    
    cout << "总单词数: " << words.size() << endl;
    
    // 插入所有单词
    int totalComparisons = 0;
    for (const auto& word : words) {
        int comparisons = list.inword(word);
        if (comparisons > 0) {
            totalComparisons += comparisons;
        }
    }
    
    double ASL = static_cast<double>(totalComparisons) / words.size();
    cout << "平均查找长度(ASL): " << fixed << setprecision(2) << ASL << endl;
    cout << "不同单词数: " << list.size() << endl;
    
    // 写入结果文件
    FileUtils::writeResults("OutFile1.txt", list.getall());
    
    // 交互式搜索
    string searchWord;
    cout << "输入要查找的单词: ";
    cin >> searchWord;
    
    int comparisons = 0;
    double time = FileUtils::getExecutionTime([&]() {
        int freq = list.search(searchWord, comparisons);
        if (freq != -1) {
            cout << "找到单词，频率为: " << freq << endl;
        } else {
            cout << "未找到单词" << endl;
        }
    });
    
    cout << "比较次数: " << comparisons << endl;
    cout << "查找时间: " << time << " 毫秒" << endl;
}

// 链表顺序查找测试
void testLinkList() {
    cout << "\n=== 链表顺序查找测试 ===" << endl;
    LinkList list;
    auto words = FileUtils::readWords("InFile.txt");
    
    cout << "总单词数: " << words.size() << endl;
    
    // 插入所有单词
    int totalComparisons = 0;
    for (const auto& word : words) {
        int comparisons = list.inword(word);
        totalComparisons += comparisons;
    }
    
    double ASL = static_cast<double>(totalComparisons) / words.size();
    cout << "平均查找长度(ASL): " << fixed << setprecision(2) << ASL << endl;
    cout << "不同单词数: " << list.size() << endl;
    
    // 写入结果文件
    FileUtils::writeResults("OutFile2.txt", list.getall());
    
    // 交互式搜索
    string searchWord;
    cout << "输入要查找的单词: ";
    cin >> searchWord;
    
    int comparisons = 0;
    double time = FileUtils::getExecutionTime([&]() {
        int freq = list.search(searchWord, comparisons);
        if (freq != -1) {
            cout << "找到单词，频率为: " << freq << endl;
        } else {
            cout << "未找到单词" << endl;
        }
    });
    
    cout << "比较次数: " << comparisons << endl;
    cout << "查找时间: " << time << " 毫秒" << endl;
}

// 折半查找测试
void testBinarySearch() {
    cout << "\n=== 折半查找测试 ===" << endl;
    BinarySearch bs(10000);
    auto words = FileUtils::readWords("InFile.txt");
    
    cout << "总单词数: " << words.size() << endl;
    
    // 插入所有单词
    int totalComparisons = 0;
    for (const auto& word : words) {
        int comparisons = bs.inword(word);
        if (comparisons > 0) {
            totalComparisons += comparisons;
        }
    }
    
    // 确保排序
    bs.sort();
    
    double ASL = static_cast<double>(totalComparisons) / words.size();
    cout << "平均查找长度(ASL): " << fixed << setprecision(2) << ASL << endl;
    cout << "不同单词数: " << bs.size() << endl;
    
    // 写入结果文件
    FileUtils::writeResults("OutFile3.txt", bs.getall());
    
    // 交互式搜索
    string searchWord;
    cout << "输入要查找的单词: ";
    cin >> searchWord;
    
    int comparisons = 0;
    double time = FileUtils::getExecutionTime([&]() {
        int freq = bs.search(searchWord, comparisons);
        if (freq != -1) {
            cout << "找到单词，频率为: " << freq << endl;
        } else {
            cout << "未找到单词" << endl;
        }
    });
    
    cout << "比较次数: " << comparisons << endl;
    cout << "查找时间: " << time << " 毫秒" << endl;
}

// 二叉搜索树测试
void testBST() {
    cout << "\n=== 二叉搜索树测试 ===" << endl;
    BSTree tree;
    auto words = FileUtils::readWords("InFile.txt");
    
    cout << "总单词数: " << words.size() << endl;
    
    // 插入所有单词
    int totalComparisons = 0;
    for (const auto& word : words) {
        int comparisons = tree.inword(word);
        if (comparisons > 0) {
            totalComparisons += comparisons;
        }
    }
    
    double ASL = static_cast<double>(totalComparisons) / words.size();
    cout << "平均查找长度(ASL): " << fixed << setprecision(2) << ASL << endl;
    
    // 写入结果文件
    FileUtils::writeResults("OutFile4.txt", tree.getall());
    
    // 交互式搜索
    string searchWord;
    cout << "输入要查找的单词: ";
    cin >> searchWord;
    
    int comparisons = 0;
    double time = FileUtils::getExecutionTime([&]() {
        int freq = tree.search(searchWord, comparisons);
        if (freq != -1) {
            cout << "找到单词，频率为: " << freq << endl;
        } else {
            cout << "未找到单词" << endl;
        }
    });
    
    cout << "比较次数: " << comparisons << endl;
    cout << "查找时间: " << time << " 毫秒" << endl;
}

// 哈希表测试
void testHashTable() {
    cout << "\n=== 哈希表测试 ===" << endl;
    HashTable ht;
    auto words = FileUtils::readWords("InFile.txt");
    
    cout << "总单词数: " << words.size() << endl;
    
    // 插入所有单词
    int totalComparisons = 0;
    for (const auto& word : words) {
        int comparisons = ht.inword(word);
        if (comparisons > 0) {
            totalComparisons += comparisons;
        }
    }
    
    double ASL = static_cast<double>(totalComparisons) / words.size();
    cout << "平均查找长度(ASL): " << fixed << setprecision(2) << ASL << endl;
    
    // 写入结果文件
    FileUtils::writeResults("OutFile5.txt", ht.getall());
    
    // 交互式搜索
    string searchWord;
    cout << "输入要查找的单词: ";
    cin >> searchWord;
    
    int comparisons = 0;
    double time = FileUtils::getExecutionTime([&]() {
        int freq = ht.search(searchWord, comparisons);
        if (freq != -1) {
            cout << "找到单词，频率为: " << freq << endl;
        } else {
            cout << "未找到单词" << endl;
        }
    });
    
    cout << "比较次数: " << comparisons << endl;
    cout << "查找时间: " << time << " 毫秒" << endl;
}

// 主菜单
int main() {
    try {
        // 创建一个测试用的文本文件
        if (!FileUtils::writeResults("InFile.txt", 
            "This is a test file to demonstrate word frequency analysis. "
            "We need to test different search algorithms and data structures. "
            "This file contains some words repeated multiple times to show "
            "how the frequency counting works. The words in this file should "
            "be processed to count frequency. This program will use different "
            "algorithms to analyze the text and demonstrate their performance. "
            "We can compare sequential search, binary search, binary search tree, "
            "and hash table implementations to see which one performs better.")) {
            cout << "无法创建测试文件，请手动创建 InFile.txt" << endl;
        }
        
        int choice;
        do {
            cout << "\n单词频率分析系统" << endl;
            cout << "1. 顺序表顺序查找" << endl;
            cout << "2. 链表顺序查找" << endl;
            cout << "3. 折半查找" << endl;
            cout << "4. 二叉搜索树查找" << endl;
            cout << "5. 哈希表查找" << endl;
            cout << "0. 退出" << endl;
            cout << "请输入选择: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    testSequentialSearch();
                    break;
                case 2:
                    testLinkList();
                    break;
                case 3:
                    testBinarySearch();
                    break;
                case 4:
                    testBST();
                    break;
                case 5:
                    testHashTable();
                    break;
                case 0:
                    cout << "再见!" << endl;
                    break;
                default:
                    cout << "无效选择，请重试!" << endl;
            }
        } while (choice != 0);
        
    } catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    }
    
    return 0;
} 