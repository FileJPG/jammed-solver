/*!
* \file
* \brief ������ ���� �������� � ���� ���������� ������� ������ Error
*/

#include "Error.h"

bool Error::operator==(const Error& other) const
{ 
	return this->type == other.type
		&& this->str == other.str
		&& this->isInitialField == other.isInitialField
		&& this->count == other.count
		&& this->fieldSize == other.fieldSize;
}

string Error::convert() const
{
	string errorString; // ����� ������

	// � ����������� �� ����������� ���� ������ � �������������� ������ �������� ������ � ������ �� ������� ��� ������ ������� ����
	switch (type) {
	case cantOpenReadFile:
		errorString = "������� ������ ���� � �������� �������. ��������, ���� �� ����������. ������������ ����: " + str;
		break;
	case cantCreateFile:
		errorString = "������� ������ ���� ��� �������� ������. �������� ���������� ������������ �� ���������� ��� ��� ���� �� �����. ������������ ����: " + str;
		break;
	case incorrectFieldForm:
		errorString = "������ �� ������� ������. ������������ ����� " + string(isInitialField ? "���������" : "�������") + " �����������.";
		break;
	case incorrectEmptyCellsCount:
		errorString = "������ �� ������� ������. ������������ ���������� ��������� ������ � " + string(isInitialField ? "���������" : "�������") + " ����������� (" + std::to_string(count) + ").";
		break;
	case incorrectSymbolsInField:
		errorString = "������ �� ������� ������. ���������� ������������ ������� � " + string(isInitialField ? "���������" : "�������") + " �����������: " + str;
		break;
	case incorrectFieldSize:
		errorString = "������ �� ������� ������. ������ ���� " + string(isInitialField ? "���������" : "�������") + " ����������� " + std::to_string(fieldSize.length) + "x" + std::to_string(fieldSize.height) + " �� �������� �������� 2x4";
		break;
	case differentSymbolsSets:
		errorString = "������ �� ������� ������. ������ ����� �������� ����� � ��������� � ������� ������������.";
		break;
	case incorrectFieldsCount:
		errorString = "������ �� ������� ������. ������������ ���������� ����������� (" + std::to_string(count) + ").";
		break;
	}
	return errorString;
}
