// ring_list.cpp
// Реализация методов циклического списка

#include "ring_list.h"

RingList::RingList() : head(nullptr), size(0) {}

RingList::~RingList() { clear(); }

void RingList::buildFromString(const std::string& digits) {
    clear();
    if (digits.empty()) return;

    head = new Node(digits[0] - '0');
    Node* tail = head;
    size = 1;

    for (size_t i = 1; i < digits.size(); ++i) {
        tail->next = new Node(digits[i] - '0');
        tail = tail->next;
        ++size;
    }
    tail->next = head; // замыкаем кольцо
}

void RingList::clear() {
    if (!head) return;

    // Разрываем кольцо, чтобы удалить линейно
    Node* cur = head;
    Node* last = head;
    while (last->next != head) last = last->next;
    last->next = nullptr;

    while (cur) {
        Node* tmp = cur;
        cur = cur->next;
        delete tmp;
    }
    head = nullptr;
    size = 0;
}

Node* RingList::getNode(int offset) const {
    if (!head || offset < 0 || offset >= size) return nullptr;
    Node* cur = head;
    for (int i = 0; i < offset; ++i) cur = cur->next;
    return cur;
}

std::string RingList::getSubstring(Node* start, int count) const {
    if (!start || count <= 0) return "";
    std::string res;
    Node* cur = start;
    for (int i = 0; i < count; ++i) {
        res.push_back('0' + cur->digit);
        cur = cur->next;
    }
    return res;
}

bool RingList::isValidNumber(const std::string& s) {
    // Число корректно, если оно состоит из одной цифры или не начинается с '0'
    return s.size() == 1 || s[0] != '0';
}

std::string RingList::toString() const {
    if (!head) return "";
    std::string res;
    Node* cur = head;
    for (int i = 0; i < size; ++i) {
        res.push_back('0' + cur->digit);
        cur = cur->next;
    }
    return res;
}