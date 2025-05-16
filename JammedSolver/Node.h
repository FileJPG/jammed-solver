/*!
* \file
* \brief ������ ���� �������� � ���� ���������� ������� ������ Node
*/

#pragma once

#include <vector>

using std::vector;

/*!
 * \brief ����
 */
template<class T> class Node
{
	T data; //!< �������� ����

	Node<T>* parent; //!< �������� (nullptr, ���� ���� �������� ������)

	vector<Node<T>*> children; //!< �������

public:

	/*!
	* \brief ����������� � �����������
	*/
	Node(T data, Node<T>* parent = nullptr, vector<Node<T>*> children = {}) : data(data), parent(parent), children(children) {}

	/*!
	* \brief ������ ��� ���� data
	*/
	const T& getData() const { return data; }

	/*!
	* \brief �������� ���� �� ����� �� ����
	* \param [in] currentNode - ������� ����, �� �������� ����� �������� ����
	* \return ���� ��������������� �� ����� �� ��������. ������ ������, ���� ���� �� �������� �������
	*/
	vector<Node<T>*> getWayFromRoot(Node<T>* currentNode) const
	{
		// ����� �� �������, ���� ������� ������ �� ��������
		if (currentNode == nullptr) 
			return {};

		vector<Node<T>*> way; // ...������� �������������� ������ ��� ������ � ���� ����� �� ����������� �������
		
		// #��������� ������ ������� ��� �������� �������� ����#, ���� ������� ���� �� �������� ������ � �������� �������� ���� �� �������� ��������� �����
		if (currentNode->parent != nullptr && currentNode->parent != this)
			way = getWayFromRoot(currentNode->parent);

		// �������� ������� ���� � �������������� ������, ���� ������� ���� �������� ������ ��� �������������� ������ �� ������
		if (currentNode->parent == nullptr || !way.empty())
			way.push_back(currentNode);

		// ������� �������������� ������
		return way;
	}
};
