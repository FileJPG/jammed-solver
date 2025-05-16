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
	cantOpenReadFile, //!< ������� ���� ������ �������/���������
	cantCreateFile, //!< �������� ���� ������ �������
	incorrectFieldForm, //!< ������������ ����� �����������
	incorrectEmptyCellsCount, //!< ������������ ���������� ������ ������ � �����������
	incorrectSymbolsInField, //!< ������������ ������ � �����������
	incorrectFieldSize,	//!< ������������ ������ �����������
	differentSymbolsSets, //!< ������ ����� � ��������� � ������� ������������
	incorrectFieldsCount //!< ������������ ���������� �����������
};

/*!
 * \brief ������
 */
class Error
{
public:
	ErrorType type; //!< ��� ������

	string str; //!< ������
	
	bool isInitialField; //!< ��������������� ����������� �������� ���������

	int count; //!< �������
	
	Size fieldSize; //!< ������� ����

	/*!
	* \brief ����������� � �����������
	*/
	Error(ErrorType type = cantOpenReadFile, string str = "", bool isInitialField = true, int count = 0, Size fieldSize = { 1, 1 }) 
		: type(type), str(str), isInitialField(isInitialField), count(count), fieldSize(fieldSize) {}

	/*!
	* \brief �������� ==
	*/
	bool operator==(const Error& other) const;

	/*!
	* \brief �������������� ������ � ��������� ������
	* \return ��������� �� ������ � ��������� �������
	*/
	string convert() const;
};
