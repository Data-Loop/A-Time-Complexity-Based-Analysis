#ifndef LINKLIST_H
#define LINKLIST_H

#include "word_count.h"
#include <string>
#include <sstream>

class LinkNode {
private:
    word_count word;
    LinkNode* next;

public:
    LinkNode(const string& w = "") : word(w), next(nullptr) {}
    
    word_count& getWord() { return word; }
    LinkNode* getNext() const { return next; }
    
    friend class LinkList;
};

class LinkList {
private:
    LinkNode* head;
    int length;
    
    // 归并排序辅助函数 - 获取中间节点
    LinkNode* getMiddle(LinkNode* head) {
        if (head == nullptr) return nullptr;
        
        LinkNode* slow = head;
        LinkNode* fast = head->next;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
    
    // 归并两个有序链表
    LinkNode* merge(LinkNode* first, LinkNode* second) {
        if (first == nullptr)
            return second;
        if (second == nullptr)
            return first;
            
        LinkNode* result = nullptr;
        
        if (first->getWord().get() <= second->getWord().get()) {
            result = first;
            result->next = merge(first->next, second);
        } else {
            result = second;
            result->next = merge(first, second->next);
        }
        
        return result;
    }

public:
    LinkList() : head(nullptr), length(0) {}
    
    ~LinkList() {
        LinkNode* current = head;
        while (current != nullptr) {
            LinkNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    // 归并排序入口
    LinkNode* mergeSort(LinkNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
            
        LinkNode* middle = getMiddle(head);
        LinkNode* nextToMiddle = middle->next;
        middle->next = nullptr;
        
        LinkNode* left = mergeSort(head);
        LinkNode* right = mergeSort(nextToMiddle);
        
        return merge(left, right);
    }
    
    // 排序链表
    void sort() {
        head = mergeSort(head);
    }
    
    // 插入单词
    int inword(const string& word) {
        int comparisons = 0;
        
        // 检查是否存在
        LinkNode* current = head;
        while (current != nullptr) {
            comparisons++;
            if (current->word.get() == word) {
                current->word.numadd();
                return comparisons;
            }
            current = current->next;
        }
        
        // 不存在则创建新节点
        LinkNode* newNode = new LinkNode(word);
        newNode->next = head;
        head = newNode;
        length++;
        
        return comparisons;
    }
    
    // 获取所有单词(需要先排序)
    string getall() {
        // 先排序
        sort();
        
        stringstream result;
        LinkNode* current = head;
        while (current != nullptr) {
            result << current->word.get() << " : " 
                   << current->word.getCount() << "\n";
            current = current->next;
        }
        
        return result.str();
    }
    
    // 顺序查找
    int search(const string& word, int& comparisons) const {
        comparisons = 0;
        LinkNode* current = head;
        
        while (current != nullptr) {
            comparisons++;
            if (current->word.get() == word) {
                return current->word.getCount();
            }
            current = current->next;
        }
        
        return -1;
    }
    
    // 获取链表长度
    int size() const {
        return length;
    }
};

#endif // LINKLIST_H 