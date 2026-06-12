#pragma once

#include <string>
#include "node.h"

class RingList {
private:
    Node* head;         // указатель на произвольный узел
    int size;           // количество узлов

public:
    RingList();
    ~RingList();

    void buildFromString(const std::string& digits);
    void fillRandom(int n);
    void clear();

    int getSize() const { return size; }

    Node* getNode(int offset) const;

    std::string getSubstring(Node* start, int count) const;

    static bool isValidNumber(const std::string& s);

    void print() const;
    std::string toString() const;
};