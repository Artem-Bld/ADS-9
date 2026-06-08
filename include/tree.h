// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>
#include <string>

class PMTree {
 private:
    struct Node {
        char value;
        std::vector<std::shared_ptr<Node>> children;
        
        Node(char val) : value(val) {}
    };
    
    std::shared_ptr<Node> root;
    int numElements;
    
    void buildTree(std::shared_ptr<Node> node, std::vector<char> remaining);
    void getAllPermsRecursive(std::shared_ptr<Node> node, std::vector<char>& current, std::vector<std::vector<char>>& result);
    std::vector<char> getPermByTraversal(int num);
    std::vector<char> getPermByNavigation(int num);
    
 public:
    PMTree(const std::vector<char>& elements);
    ~PMTree() = default;
    
    friend std::vector<std::vector<char>> getAllPerms(PMTree& tree);
    friend std::vector<char> getPerm1(PMTree& tree, int num);
    friend std::vector<char> getPerm2(PMTree& tree, int num);
    
    int getTotalPermutations() const;
    std::shared_ptr<Node> getRoot() const { return root; }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
