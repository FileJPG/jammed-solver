#pragma once

#include <vector>

using std::vector;

// Очередь с приоритетом
template<class T> class PriorityQueue
{
    // Элементы очереди
    vector<T> items;

    // Приоритеты элементов очереди
    vector<int> priorities;
};
