// Copyright 2022 NNTU-CS
#include <algorithm>
#include <memory>
#include <vector>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {
    if (elements.empty()) {
        root = nullptr;
        numElements = 0;
        return;
    }

    numElements = elements.size();
    root = std::make_shared<Node>(Node('\0'));

    std::vector<char> sorted = elements;
    std::sort(sorted.begin(), sorted.end());

    buildTree(root, sorted);
}

void PMTree::buildTree(std::shared_ptr<Node> node,
                       std::vector<char> remaining) {
    if (remaining.empty()) {
        return;
    }

    for (char c : remaining) {
        auto child = std::make_shared<Node>(c);
        node->children.push_back(child);

        std::vector<char> newRemaining;
        for (char r : remaining) {
            if (r != c) {
                newRemaining.push_back(r);
            }
        }

        buildTree(child, newRemaining);
    }
}

void PMTree::getAllPermsRecursive(std::shared_ptr<Node> node,
                                  std::vector<char>& current,
                                  std::vector<std::vector<char>>& result) {
    if (!node || node->value == '\0') {
        return;
    }

    current.push_back(node->value);

    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (auto& child : node->children) {
            getAllPermsRecursive(child, current, result);
        }
    }

    current.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;

    if (!tree.root || tree.root->children.empty()) {
        return result;
    }

    std::vector<char> current;

    for (auto& child : tree.root->children) {
        tree.getAllPermsRecursive(child, current, result);
    }

    return result;
}

std::vector<char> PMTree::getPermByTraversal(int num) {
    if (num < 1) {
        return std::vector<char>();
    }

    auto allPerms = getAllPerms(*this);

    if (num > static_cast<int>(allPerms.size())) {
        return std::vector<char>();
    }

    return allPerms[num - 1];
}

static int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

std::vector<char> PMTree::getPermByNavigation(int num) {
    if (num < 1 || !root || root->children.empty()) {
        return std::vector<char>();
    }

    int remaining = num - 1;
    std::vector<char> result;
    std::shared_ptr<Node> current = root;

    int levelsLeft = numElements;

    while (current->children.size() > 0 && levelsLeft > 0) {
        int childrenCount = current->children.size();
        int blockSize = factorial(levelsLeft - 1);
        int childIndex = remaining / blockSize;

        if (childIndex >= childrenCount) {
            return std::vector<char>();
        }

        result.push_back(current->children[childIndex]->value);
        remaining = remaining % blockSize;
        current = current->children[childIndex];
        levelsLeft--;
    }

    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    return tree.getPermByTraversal(num);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    return tree.getPermByNavigation(num);
}

int PMTree::getTotalPermutations() const {
    return factorial(numElements);
}
