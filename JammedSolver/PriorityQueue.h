/*!
* \file
* \brief ������ ���� �������� ������������ ������ ��� ������ PriorityQueue
*/

#pragma once

#include <vector>

using std::vector;

/*!
 * \brief ������� � �����������
 */
template<class T> class PriorityQueue
{
    vector<T*> items; // �������� �������

    vector<int> priorities; // ���������� ��������� �������

public:

    /*!
    * \brief �������� � ������� ������� � �����������
    * \param [in] item - ����� �������
    * \param [in] priority - ��������� ��������
    */
    void enqueue(const T* item, const int& priority);

    /*!
    * \brief ����� �� ������� ������� � ���������� ����������� (���������� ���������)
    * \return ������� ������� � ���������� �����������. � ������ ��������� ����� ��������� ���������� ���, ������� ��� �������� ������
    */
    T* dequeue();
};
