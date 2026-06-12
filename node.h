#pragma once
struct Node {
    int digit;  
    Node* next;

    Node(int d = 0, Node* n = nullptr) : digit(d), next(n) {}
};
