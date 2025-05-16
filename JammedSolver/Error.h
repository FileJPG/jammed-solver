/*!
* \file
* \brief Данный файл является заголовочным файлом для класса Error
*/

#pragma once

#include <string>
#include "Structure.h"

using std::string;

/*!
 * \brief Тип ошибки
 */
enum ErrorType
{
	cantOpenReadFile, //!< Входной файл нельзя открыть/прочитать
	cantCreateFile, //!< Выходной файл нельзя создать
	incorrectFieldForm, //!< Некорректная форма расстановки
	incorrectEmptyCellsCount, //!< Некорректное количество пустых клеток в расстановке
	incorrectSymbolsInField, //!< Некорректный символ в расстановке
	incorrectFieldSize,	//!< Некорректный размер расстановки
	differentSymbolsSets, //!< Разные фишки в начальной и целевой расстановках
	incorrectFieldsCount //!< Некорректное количество расстановок
};

/*!
 * \brief Ошибка
 */
class Error
{
public:
	ErrorType type; //!< Тип ошибки

	string str; //!< Строка
	
	bool isInitialField; //!< Рассматриваемая расстановка является начальной

	int count; //!< Счетчик
	
	Size fieldSize; //!< Размеры поля

	/*!
	* \brief Конструктор с аргументами
	*/
	Error(ErrorType type = cantOpenReadFile, string str = "", bool isInitialField = true, int count = 0, Size fieldSize = { 1, 1 }) 
		: type(type), str(str), isInitialField(isInitialField), count(count), fieldSize(fieldSize) {}

	/*!
	* \brief Оператор ==
	*/
	bool operator==(const Error& other) const;

	/*!
	* \brief Конвертировать ошибку в строковый формат
	* \return Сообщение об ошибке в строковом формате
	*/
	string convert() const;
};
