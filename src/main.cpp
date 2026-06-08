// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "tree.h"

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    auto perms = getAllPerms(tree);
    std::cout << "All permutations of 1,2,3:\n";
    for (const auto& p : perms) {
        for (char c : p) std::cout << c;
        std::cout << '\n';
    }

    std::cout << "\ngetPerm1(tree,1): ";
    for (char c : getPerm1(tree, 1)) std::cout << c;
    std::cout << "\ngetPerm2(tree,2): ";
    for (char c : getPerm2(tree, 2)) std::cout << c;
    std::cout << "\ngetPerm1(tree,6): ";
    for (char c : getPerm1(tree, 6)) std::cout << c;
    std::cout << '\n';

    std::cout << "\n--- Experiment ---\n";
    std::cout << "n\tgetAllPerms(s)\tgetPerm1(s)\tgetPerm2(s)\n";

    std::mt19937 rng(42);
    for (int n = 3; n <= 8; ++n) {
        std::vector<char> v;
        for (int i = 0; i < n; ++i) v.push_back('1' + i);
        PMTree t(v);

        int total = 1;
        for (int i = 2; i <= n; ++i) total *= i;
        std::uniform_int_distribution<int> dist(1, total);

        auto t1 = std::chrono::high_resolution_clock::now();
        auto all = getAllPerms(t);
        auto t2 = std::chrono::high_resolution_clock::now();
        double tAll = std::chrono::duration<double>(t2 - t1).count();

        int num = dist(rng);
        auto t3 = std::chrono::high_resolution_clock::now();
        auto r1 = getPerm1(t, num);
        auto t4 = std::chrono::high_resolution_clock::now();
        double tP1 = std::chrono::duration<double>(t4 - t3).count();

        auto t5 = std::chrono::high_resolution_clock::now();
        auto r2 = getPerm2(t, num);
        auto t6 = std::chrono::high_resolution_clock::now();
        double tP2 = std::chrono::duration<double>(t6 - t5).count();

        std::cout << n << '\t' << tAll << "\t\t"
                  << tP1 << "\t\t" << tP2 << '\n';
    }
    return 0;
}
