/*!
* \file
* \brief Данный файл является заголовочным файлом для класса Node
*/

#pragma once

#include <vector>

using std::vector;

/*!
 * \brief Узел
 */
template<class T> class Node
{
	T data; // Значение узла

	Node<T>* parent; // Родитель (nullptr, если узел является корнем)

	vector<Node<T>*> children; // Потомки

public:

	/*!
	* \brief Получить путь от корня до узла
	* \param [in] currentNode - текущий узел, до которого нужно получить путь
	* \return Узлы последовательно от корня до текущего. Пустой вектор, если граф не является деревом
	*/
	vector<Node<T>*> getWayFromRoot(const Node<T>* currentNode) const;
};
