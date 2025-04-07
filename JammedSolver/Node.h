/*!
* \file
* \brief ������ ���� �������� ������������ ������ ��� ������ Node
*/

#pragma once

#include <vector>

using std::vector;

/*!
 * \brief ����
 */
template<class T> class Node
{
	T data; // �������� ����

	Node<T>* parent; // �������� (nullptr, ���� ���� �������� ������)

	vector<Node<T>*> children; // �������

public:

	/*!
	* \brief �������� ���� �� ����� �� ����
	* \param [in] currentNode - ������� ����, �� �������� ����� �������� ����
	* \return ���� ��������������� �� ����� �� ��������. ������ ������, ���� ���� �� �������� �������
	*/
	vector<Node<T>*> getWayFromRoot(const Node<T>* currentNode) const;
};
