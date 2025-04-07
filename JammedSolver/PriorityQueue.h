/*!
* \file
* \brief Данный файл является заголовочным файлом для класса PriorityQueue
*/

#pragma once

#include <vector>

using std::vector;

/*!
 * \brief Очередь с приоритетом
 */
template<class T> class PriorityQueue
{
    vector<T*> items; // Элементы очереди

    vector<int> priorities; // Приоритеты элементов очереди

public:

    /*!
    * \brief Добавить в очередь элемент с приоритетом
    * \param [in] item - новый элемент
    * \param [in] priority - приоритет элемента
    */
    void enqueue(const T* item, const int& priority);

    /*!
    * \brief Взять из очереди элемент с наибольшим приоритетом (наименьшим значением)
    * \return Элемент очереди с наибольшим приоритетом. В случае множества таких элементов выбирается тот, который был добавлен раньше
    */
    T* dequeue();
};
