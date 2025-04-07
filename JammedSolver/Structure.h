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
    int lenght; // �����
    int height; // ������
};
