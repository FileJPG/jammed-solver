/*!
* \file
* \brief ������ ���� �������� ������������ ������ ��� ������ Error
*/

#pragma once

#include <string>
#include "Structure.h"

using std::string;

/*!
 * \brief ��� ������
 */
enum ErrorType
{
	cantOpenReadFile, // ������� ���� ������ �������/���������
	cantCreateFile, // �������� ���� ������ �������
	incorrectFieldForm, // ������������ ����� �����������
	incorrectEmptyCellsCount, // ������������ ���������� ������ ������ � �����������
	incorrectSymbolsInField, // ������������ ������ � �����������
	incorrectFieldSize,	// ������������ ������ �����������
	differentSymbolsSets, // ������ ����� � ��������� � ������� ������������
	incorrectFieldsCount // ������������ ���������� �����������
};

/*!
 * \brief ������
 */
class Error
{
public:
	ErrorType type; // ��� ������

	string str; // ������
	
	bool isInitialField; // ��������������� ����������� �������� ���������

	int count; // �������
	
	Size fieldSize; // ������� ����

	/*!
	* \brief �������������� ������ � ��������� ������
	* \return ��������� �� ������ � ��������� �������
	*/
	string convert() const;
};
