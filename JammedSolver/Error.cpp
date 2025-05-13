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
