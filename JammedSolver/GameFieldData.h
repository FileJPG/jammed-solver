/*!
* \file
* \brief ������ ���� �������� ������������ ������ ��� ������ GameFieldData
*/

#pragma once

#include <vector>

#include "Structure.h"
#include "Error.h"

using std::vector;

using Field = vector<vector<char>>; // ��������� ��� �������� ����

/*!
 * \brief ������� ���� � ��������������� �������
 */
class GameFieldData
{
    Field field; // ������� ����

    int numberOfMoves; // ���������� ��������� �����

    int manhattanDistance; // ������������� ����������

public:

    /*!
    * \brief ��������� ����������� ����� �� ����������
    * \param [in] field - �����������
    * \return ������ � �����������
    */
    static vector<Error> validate(const Field& field);

    /*!
    * \brief �������� ����������� �����
    * \param [in] firstField - ������ �����������
    * \param [in] secondField - ������ �����������
    * \return ����������� �������� �����������
    */
    static bool compareFields(const GameFieldData& firstField, const GameFieldData& secondField);

    /*!
    * \brief �������� ������ ����� � ������������
    * \param [in] firstField - ������ �����������
    * \param [in] secondField - ������ �����������
    * \return ����������� ����� ���������� ����� �����
    */
    static bool compareSets(const GameFieldData& firstField, const GameFieldData& secondField);

    /*!
    * \brief �������� ������ �����������
    * \return ������ ����������� �� ����������� � ���������
    */
    Size getSize() const;

    /*!
    * \brief ������� ��������� ���� ��� �����������
    * \return ��� ��������� ����
    */
    vector<GameFieldData> getMoves() const;

    /*! ��������� ������������� ���������� �� ����������� �����
    * \param [in] goalField - ������� �����������
    * \return ������������� ���������� ��� ���� �����
    */
    int getManhattanDistance(const GameFieldData& goalField) const;

    /*!
    * \brief ����������� ����� �� ������ ������
    * \param [in] direction - ����������� ����������� ������ ������
    * \return ����������� �������
    */
    bool swap(const Direction& direction);

private:

    /*!
    * \brief �������� ������� ������ � �����������
    * \param [in] value - �������� ������ ������
    * \return ������� ������ ������
    */
    vector<Position> getPos(const char& value) const;
};
