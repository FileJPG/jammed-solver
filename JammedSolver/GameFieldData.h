/*!
* \file
* \brief ������ ���� �������� ������������ ������ ��� ������ GameFieldData
*/

#pragma once

#include <vector>
#include "Structure.h"
#include "Error.h"

using std::vector;

using Field = vector<vector<char>>; //!< ��������� ��� �������� ����

const Field DEFAULT_FIELD = { {'#'} }; //!< ���� �� ���������

/*!
 * \brief ������� ���� � ��������������� �������
 */
class GameFieldData
{
    friend vector<GameFieldData> solveJammed(const GameFieldData& startField, const GameFieldData& goalField);

    Field field; //!< ������� ����

    int numberOfMoves; //!< ���������� ��������� �����

    int manhattanDistance; //!< ������������� ����������

public:

    /*!
    * \brief ����������� � �����������
    */
    GameFieldData(const Field& field = DEFAULT_FIELD, const int& numberOfMoves = 0, const int& manhattanDistance = -1);

    /*!
    * \brief �������� ==
    */
    bool operator==(const GameFieldData& other);

    /*!
    * \brief ������ ��� ���� field
    */
    bool setField(Field newField);

    /*!
    * \brief ������ ��� ���� field
    */
    Field getField() const;

    /*!
    * \brief ������ ��� �������� �����������
    */
    Size getSize() const;

    /*!
    * \brief ������ ��� ���� numberOfMoves
    */
    int getNumberOfMoves() const;

    /*!
    * \brief ������ ��� ���� manhattanDistance
    */
    int getManhattanDistance() const;

    /*!
    * \brief ������ ��� ���������� ��������� �����
    */
    void setNumberOfMoves(const int& value);

    /*!
    * \brief ������ ��� ���� manhattanDistance
    */
    void setManhattanDistance(const int& value);

    /*!
    * \brief ��������� ����������� ����� �� ����������
    * \param [in] field - �����������
    * \return ������ � �����������
    */
    static vector<Error> validate(const Field& field);

    /*!
    * \brief �������� ���������� ����
    * \param [in] startField - ��������� �����������
    * \param [in] goalField - ������� �����������
    * \return ������� ����������� �������� ���������� �� ���������
    */
    static bool isSolvable(const GameFieldData& startField, const GameFieldData& goalField);

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
    * \brief ������������� ������ �����������
    * \param [in] rawField - ����������� � ������� vector<string>
    * \return ����������� � ������� Field
    */
    static Field convert(const vector<string>& rawField);

    /*!
    * \brief ������� ��������� ���� ��� �����������
    * \return ��� ��������� ����
    */
    vector<GameFieldData> getMoves() const;

    /*!
    * \brief ��������� ������������� ���������� �� ����������� �����
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

    /*!
    * \brief �������� ������� ������ � �����������
    * \param [in] value - �������� ������ ������
    * \return ������� ������ ������
    */
    vector<Position> getPos(const char& value) const;

    /*!
    * \brief ��������� ���������� �������� � �����������
    * \return ���������� �������� � �����������
    */
    int countInversions() const;
};
