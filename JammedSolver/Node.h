/*!
* \file
* \brief Данный файл содержит в себе реализацию функций класса Node
*/

#pragma once

#include <vector>

using std::vector;

/*!
 * \brief Узел
 */
template<class T> class Node
{
	T data; //!< Значение узла

	Node<T>* parent; //!< Родитель (nullptr, если узел является корнем)

	vector<Node<T>*> children; //!< Потомки

public:

	/*!
	* \brief Конструктор с параметрами
	*/
	Node(T data, Node<T>* parent = nullptr, vector<Node<T>*> children = {}) : data(data), parent(parent), children(children) {}

	/*!
	* \brief Геттер для поля data
	*/
	const T& getData() const { return data; }

	/*!
	* \brief Получить путь от корня до узла
	* \param [in] currentNode - текущий узел, до которого нужно получить путь
	* \return Узлы последовательно от корня до текущего. Пустой вектор, если граф не является деревом
	*/
	vector<Node<T>*> getWayFromRoot(Node<T>* currentNode) const
	{
		// Выйти из функции, если входные данные не валидные
		if (currentNode == nullptr) 
			return {};

		vector<Node<T>*> way; // ...Создать результирующий вектор для записи в него узлов из рекурсивной функции
		
		// #Выполнить данную функцию для родителя текущего узла#, если текущий узел не является корнем и родитель текущего узла не является начальным узлом
		if (currentNode->parent != nullptr && currentNode->parent != this)
			way = getWayFromRoot(currentNode->parent);

		// Положить текущий узел в результирующий вектор, если текущий узел является корнем или результирующий вектор не пустой
		if (currentNode->parent == nullptr || !way.empty())
			way.push_back(currentNode);

		// Вернуть результирующий вектор
		return way;
	}
};
