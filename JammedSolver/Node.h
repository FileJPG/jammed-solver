#pragma once

#include <vector>

using std::vector;

// ����
template<class T> class Node
{
	// �������� ����
	T data;

	// ����-�������� (nullptr, ���� ���� �������� ������)
	Node<T>* parent;

	// ����-�������
	vector<Node<T>*> children;
};
