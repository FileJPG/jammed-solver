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
};

/*!
* \brief ������
*/
struct Size
{
    int length; // �����
    int height; // ������

    /*!
    * \brief �������� !=
    */
    bool operator!=(const Size& other) { return length != other.length || height != other.height; }

    /*!
    * \brief �������� �������
    * \return ������� ��� ������ ��������
    */
    int square() { return length * height; }

    /*!
    * \brief �������� �������
    * \param [in] other - ������ ������
    * \return ������� ����������
    */
    bool compare(const Size& other) { return length == other.length && height == other.height; }
};
