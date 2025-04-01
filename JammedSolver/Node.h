#pragma once

#include <vector>

using std::vector;

// Узел
template<class T> class Node
{
	// Значение узла
	T data;

	// Узел-родитель (nullptr, если узел является корнем)
	Node<T>* parent;

	// Узлы-потомки
	vector<Node<T>*> children;
};
