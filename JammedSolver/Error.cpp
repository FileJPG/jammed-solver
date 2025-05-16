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

string Error::convert() const
{
	string errorString; // Текст ошибки

	// В зависимости от переданного кода ошибки и дополнительных данных записать ошибку в строку по шаблону для ошибки данного типа
	switch (type) {
	case cantOpenReadFile:
		errorString = "Неверно указан файл с входными данными. Возможно, файл не существует. Используемый путь: " + str;
		break;
	case cantCreateFile:
		errorString = "Неверно указан файл для выходных данных. Возможно указанного расположения не существует или нет прав на зпись. Используемый путь: " + str;
		break;
	case incorrectFieldForm:
		errorString = "Ошибка во входных данных. Некорректная форма " + string(isInitialField ? "начальной" : "целевой") + " расстановки.";
		break;
	case incorrectEmptyCellsCount:
		errorString = "Ошибка во входных данных. Некорректное количество свободных клеток в " + string(isInitialField ? "начальной" : "целевой") + " расстановке (" + std::to_string(count) + ").";
		break;
	case incorrectSymbolsInField:
		errorString = "Ошибка во входных данных. Обнаружены недопустимые символы в " + string(isInitialField ? "начальной" : "целевой") + " расстановке: " + str;
		break;
	case incorrectFieldSize:
		errorString = "Ошибка во входных данных. Размер поля " + string(isInitialField ? "начальной" : "целевой") + " расстановки " + std::to_string(fieldSize.length) + "x" + std::to_string(fieldSize.height) + " не является размером 2x4";
		break;
	case differentSymbolsSets:
		errorString = "Ошибка во входных данных. Разный набор значений фишек в начальной и целевой расстановках.";
		break;
	case incorrectFieldsCount:
		errorString = "Ошибка во входных данных. Некорректное количество расстановок (" + std::to_string(count) + ").";
		break;
	}
	return errorString;
}
