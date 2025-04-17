#ifndef BSTREE_H
#define BSTREE_H

#include "word_count.h"
#include <string>
#include <sstream>

class TreeNode {
private:
    word_count word;
    TreeNode* left;
    TreeNode* right;
    
public:
    TreeNode(const string& w) : word(w), left(nullptr), right(nullptr) {}
    friend class BSTree;
};

class BSTree {
private:
    TreeNode* root;
    int nodeCount;
    
    // 中序遍历辅助函数
    void inorderTraversal(TreeNode* node, string& result) const {
        if (node != nullptr) {
            inorderTraversal(node->left, result);
            result += node->word.get() + " : " + 
                     to_string(node->word.getCount()) + "\n";
            inorderTraversal(node->right, result);
        }
    }
    
    // 销毁树
    void destroyTree(TreeNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
public:
    BSTree() : root(nullptr), nodeCount(0) {}
    
    ~BSTree() {
        destroyTree(root);
    }
    
    // 插入单词
    int inword(const string& word) {
        if (root == nullptr) {
            root = new TreeNode(word);
            nodeCount++;
            return 1;
        }

        TreeNode* current = root;
        TreeNode* parent = nullptr;
        int comparisons = 0;

        while (current != nullptr) {
            comparisons++;
            if (current->word.get() == word) {
                current->word.numadd();
                return comparisons;
            }

            parent = current;
            if (word < current->word.get()) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (nodeCount < 5000) {
            TreeNode* newNode = new TreeNode(word);
            if (word < parent->word.get()) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
            nodeCount++;
            return comparisons;
        }

        return -1;
    }
    
    // 获取所有单词(按字典序)
    string getall() const {
        string result;
        inorderTraversal(root, result);
        return result;
    }
    
    // 查找单词
    int search(const string& word, int& comparisons) const {
        comparisons = 0;
        TreeNode* current = root;
        
        while (current != nullptr) {
            comparisons++;
            if (current->word.get() == word) {
                return current->word.getCount();
            }
            
            if (word < current->word.get()) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        return -1;
    }
};

#endif // BSTREE_H 