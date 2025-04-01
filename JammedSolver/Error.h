#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

// Тип ошибки
enum ErrorType
{
	none, // Нет ошибки
	cantOpenReadFile, // Входной файл нельзя открыть/прочитать
	cantCreateFile, // Выходной файл нельзя создать
	incorrectEmptyCellsCount, // Некорректное количество пустых клеток в расстановке
	incorrectSymbolsInField, // Некорректный символ в расстановке
	incorrectFieldSize,	// Некорректный размер расстановки
	differentSymbolsSets, // Разные фишки в начальной и целевой расстановках
	incorrectFieldsCount // Некорректное количество расстановок
};

// Ошибка
class Error
{
	// Тип ошибки
	ErrorType type;

	// Путь к входному файлу
	string filePath;
	
	// Рассматриваемая расстановка является начальной
	bool isInitialField;

	// Счетчик чего-либо
	int count;
	
	// Неправильные символы
	vector<char> symbols;
	
	// Размеры поля
	int fieldSizeX, fieldSizeY;
};
