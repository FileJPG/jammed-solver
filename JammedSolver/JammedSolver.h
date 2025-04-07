/*!
* \file
* \brief ������ ���� �������� ������������ ������ ��� ���������
*/

#pragma once

#include <vector>
#include <string>

#include "GameFieldData.h"
#include "Error.h"

using std::vector;
using std::string;

/*!
* \brief ��������� ������ �� ����� ���������
* \param [in] filePath - ���� � �������� �����
* \param [out] data - ����������� ������
* \return ���� ������� ������
*/
bool readFile(const string& filePath, vector<string>& data);

/*!
* \brief ��������� ����� �� ����� �������-������������
* \param [in] text - �����
* \param [in] separator - ������-�����������
* \return ����� ������
*/
vector<vector<string>> parseText(const vector<string>& text, const string& separator);

/*!
* \brief ������ ���� "Jammed"
* \param [in] startField - ��������� ����������� �����
* \param [in] goalField - ������� ����������� �����
* \return ������������������ ����������� �� ��������� �� �������. ������ ������, ���� ������� ���
*/
vector<GameFieldData> solveJammed(const GameFieldData& startField, const GameFieldData& goalField);
