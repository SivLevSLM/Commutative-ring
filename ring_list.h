// ring_list.h
// Циклический односвязный список цифр для представления кольца

#pragma once
#include <string>
#include "node.h"

class RingList {
private:
    Node* head;   // указатель на произвольный узел (начало обхода)
    int size;     // количество узлов

public:
    RingList();
    ~RingList();

    // Строит кольцо из строки цифр
    void buildFromString(const std::string& digits);

    // Очищает список (удаляет все узлы)
    void clear();

    // Возвращает размер списка
    int getSize() const { return size; }

    // Возвращает указатель на узел с заданным смещением от head
    Node* getNode(int offset) const;

    // Извлекает строку из count узлов, начиная с заданного узла
    std::string getSubstring(Node* start, int count) const;

    // Проверяет, что строка может быть числом
    static bool isValidNumber(const std::string& s);

    // Возвращает строковое представление всего кольца
    std::string toString() const;
};
