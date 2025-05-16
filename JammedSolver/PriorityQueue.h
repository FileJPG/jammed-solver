/*!
* \file
* \brief ������ ���� �������� � ���� ���������� ������� ������ PriorityQueue
*/

#pragma once

#include <vector>
#include <algorithm>

using std::vector;

/*!
 * \brief ������� � �����������
 */
template<class T> class PriorityQueue
{
    vector<T*> items; //!< �������� �������

    vector<int> priorities; //!< ���������� ��������� �������

public:

	/*!
	* \brief ������ ��� ���� items
	*/
	const vector<T*>& getItems() const { return items; }

	/*!
	* \brief ������ ��� ���� priorities
	*/
	const vector<int>& getPriorities() const { return priorities; }

	/*!
	* \brief ���������, �������� �� ������� ������
	* \return ������� �������� ������
	*/
	bool isEmpty() const { return items.empty(); }

    /*!
    * \brief �������� � ������� ������� � �����������
    * \param [in] item - ����� �������
    * \param [in] priority - ��������� ��������
    */
    void enqueue(T* item, int priority)
	{
		// �������� � ����� ������� ��������� ������� ����� �������
		items.push_back(item);

		// �������� � ����� ������� ����������� ��������� ������� ��������� ������ ��������
		priorities.push_back(priority);
	}

    /*!
    * \brief ����� �� ������� ������� � ���������� ����������� (���������� ���������)
    * \return ������� ������� � ���������� �����������. � ������ ��������� ����� ��������� ���������� ���, ������� ��� �������� ������
    */
    T* dequeue()
	{
		// ������� ������� ���������, ���� � ������� ��� ���������
		if (items.empty())
			return nullptr;

		// ��������� � ������� ����������� ��������� ������� ������� ���������� � ���������� ���������
		auto minItemIterator = std::min_element(priorities.cbegin(), priorities.cend());
		int minItemIndex = std::distance(priorities.cbegin(), minItemIterator);

		// ��������� ������� � ������� ��������� �� ��������� �������
		T* dequeuedItem = items[minItemIndex];

		// ������� � ����� �������� �������� �� ��������� �������
		items.erase(items.cbegin() + minItemIndex);
		priorities.erase(priorities.cbegin() + minItemIndex);

		// ������� ����������� �������
		return dequeuedItem;
	}
};
