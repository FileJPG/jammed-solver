/*!
* \file
* \brief Данный файл содержит в себе реализацию функций класса Error
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
