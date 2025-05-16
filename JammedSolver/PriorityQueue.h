/*!
* \file
* \brief Данный файл содержит в себе реализацию функций класса PriorityQueue
*/

#pragma once

#include <vector>
#include <algorithm>

using std::vector;

/*!
 * \brief Очередь с приоритетом
 */
template<class T> class PriorityQueue
{
    vector<T*> items; //!< Элементы очереди

    vector<int> priorities; //!< Приоритеты элементов очереди

public:

	/*!
	* \brief Геттер для поля items
	*/
	const vector<T*>& getItems() const { return items; }

	/*!
	* \brief Геттер для поля priorities
	*/
	const vector<int>& getPriorities() const { return priorities; }

	/*!
	* \brief Проверить, является ли очередь пустой
	* \return Очередь является пустой
	*/
	bool isEmpty() const { return items.empty(); }

    /*!
    * \brief Добавить в очередь элемент с приоритетом
    * \param [in] item - новый элемент
    * \param [in] priority - приоритет элемента
    */
    void enqueue(T* item, int priority)
	{
		// Добавить в конец вектора элементов очереди новый элемент
		items.push_back(item);

		// Добавить в конец вектора приоритетов элементов очереди приоритет нового элемента
		priorities.push_back(priority);
	}

    /*!
    * \brief Взять из очереди элемент с наибольшим приоритетом (наименьшим значением)
    * \return Элемент очереди с наибольшим приоритетом. В случае множества таких элементов выбирается тот, который был добавлен раньше
    */
    T* dequeue()
	{
		// Вернуть нулевой указатель, если в очереди нет элементов
		if (items.empty())
			return nullptr;

		// Вычислить в векторе приоритетов элементов позицию первого приоритета с наименьшим значением
		auto minItemIterator = std::min_element(priorities.cbegin(), priorities.cend());
		int minItemIndex = std::distance(priorities.cbegin(), minItemIterator);

		// Запомнить элемент в векторе элементов по найденной позиции
		T* dequeuedItem = items[minItemIndex];

		// Удалить в обоих векторах элементы по найденной позиции
		items.erase(items.cbegin() + minItemIndex);
		priorities.erase(priorities.cbegin() + minItemIndex);

		// Вернуть запомненный элемент
		return dequeuedItem;
	}
};
