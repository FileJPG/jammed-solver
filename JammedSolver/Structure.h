/*!
* \file
* \brief ������ ���� �������� ������������ ������ ��� �������������� �������� � ������������
*/

#pragma once

/*!
* \brief �����������
*/
enum Direction
{
    up, // �����
    down, // ����
    right, // ������
    left // �����
};

/*!
* \brief �������
*/
struct Position
{
    int x; // ���������� �� �����������
    int y; // ���������� �� ���������

    /*!
    * \brief �������� ==
    */
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
};

/*!
* \brief ������
*/
struct Size
{
    int length; // �����
    int height; // ������

    /*!
    * \brief �������� ==
    */
    bool operator==(const Size& other) const { return length == other.length && height == other.height; }

    /*!
    * \brief �������� !=
    */
    bool operator!=(const Size& other) const { return !operator==(other); }

    /*!
    * \brief �������� �������
    * \return ������� ��� ������ ��������
    */
    int square() const { return length * height; }

    /*!
    * \brief �������� �������
    * \param [in] other - ������ ������
    * \return ������� ����������
    */
    bool compare(const Size& other) const { return operator==(other); }
};
