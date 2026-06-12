// node.h
// узел односвязного списка для хранения одной цифры.

#pragma once
struct Node {
    int digit;          // цифра (0-9)
    Node* next;         // указатель на следующий узел

    // конструктор узла
    Node(int d = 0, Node* n = nullptr) : digit(d), next(n) {}
};