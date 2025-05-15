/*!
* \file
* \brief Данный файл содержит главную функцию программы JammedSolver.
*
* \mainpage Документация для программы "JammedSolver"
Программа предназначена для осуществления решения игры "Пятнашки".
Для функционирования программы необходима операционная система Windows 7 или выше.
Программа разработана на языке С++ с использованием стандартных библиотек.
Программа должна получать два аргумента командной строки: имя входного файла и имя выходного файла в формате 'txt'.

Пример команды запуска программы:
* \code
./JammedSolver.exe ./input.txt ./output.txt
* \endcode

* \author Ivan Maltsev
* \date May 2025
* \version 1.0
*/

#include <iostream>
#include <fstream>
#include <locale>
#include "JammedSolver.h"

#define FIELDS_SEPARATOR ""
#define FIELD_HEIGHT 2
#define FIELD_LENGTH 4

/*!
 * \brief Главная функция программы
 * \param [in] argc - количество переданных аргументов командной строки
 * \param [in] argv - аргументы командной строки
 * \param [in] argv[0] - аргумент запуска программы
 * \param [in] argv[1] - путь к входному файлу
 * \param [in] argv[2] - путь к выходному файлу
 * \return 0 - программа завершилась без исключений
 */
int main(int argc, char* argv[])
{
    // Включить поддержку русского языка в консоли
	setlocale(LC_ALL, "Russian");

	// Анализ переданных в программу аргументов
	if (argc != 3) {
		std::cout << "Ошибка: программа принимает три аргумента: '<путь к программе> <путь к входному файлу> <путь к выходному файлу>'" << std::endl;
		return 0;
	}

	GameFieldData startField; // Начальная расстановка
	GameFieldData goalField; // Целевая расстановка
	vector<Error> errors; // Набор возникших ошибок при работе программы

	// #Прочитать данные из входного файла# и добавить ошибку, если файл не открывается
	vector<string> data; // Данные из входного файла
	bool fileOpened = readFile(argv[1], data);

	if (!fileOpened)
		errors.push_back(Error(cantOpenReadFile, argv[1]));

	// Прочитать начальную и целевую расстановки фишек...
	if (fileOpened) // Если удалось открыть входной файл
	{
		// #Преобразовать прочитанные из файла данные в расстановки#
		vector<vector<string>> rawFields = parseText(data, FIELDS_SEPARATOR);
		
		vector<Field> fields; // Расстановки в формате игровых полей
		for (const auto& rawField : rawFields)
			fields.push_back(GameFieldData::convert(rawField));

		// Добавить ошибку, если начальная или целевая расстановка не найдена
		if (fields.size() < 2)
			errors.push_back(Error(incorrectFieldsCount, "", true, fields.size()));

		for (int i = 0; i < fields.size() && i < 2; i++) // Для каждой расстановки (начальной и целевой)
		{
			// Добавить ошибку текущей расстановки, если #она не валидная#
			vector<Error> fieldErrors = GameFieldData::validate(fields[i]);

			for (auto& fieldError : fieldErrors)
				fieldError.isInitialField = i == 0 ? true : false;

			// Добавить ошибку текущей расстановки, если она имеет неправильный размер
			if (fields[i].size() != FIELD_HEIGHT || fields[i][0].size() != FIELD_LENGTH)
				errors.push_back(Error(incorrectFieldSize, "", i == 0 ? true : false, 0, Size{ static_cast<int>(fields[i].size()), static_cast<int>(fields[i][0].size()) } ));
		}

		// Добавить ошибку, если найдены обе расстановки, и #они имеют разный набор фишек#
		if (fields.size() >= 2) 
		{
			// Создать расстановки в нужном формате
			startField.setField(fields[0]);
			goalField.setField(fields[1]);

			// Добавить ошибку
			if (!GameFieldData::compareSets(startField, goalField))
				errors.push_back(Error(differentSymbolsSets));
		}
	}
	
	// Выполнить программу и записать данные в выходной файл...
	
	// ...Создать выходной файл и добавить ошибку, если файл не создается
	std::ofstream outputFile(argv[2]);
	if (!outputFile)
		errors.push_back(Error(cantCreateFile, argv[2]));

	if (errors.empty()) // Если не произошло ошибок при чтении расстановок и создании выходного файла
	{
		// #Решить игру#
		vector<GameFieldData> solution = solveJammed(startField, goalField);

		// Вывести отсутствие решения, если у игры нет решения...
		if (solution.empty()) // Если решения нет
		{
			// Записать "Нет решений" в выходной файл
			outputFile << "Нет решений" << std::endl;

			// Завершить программу
			return 0;
		}

		// Вывести в выходной файл количество ходов от начальной расстановки к целевой и отступить строку
		outputFile << solution.size() - 1 << std::endl << std::endl;

		// Вывести в выходной файл последовательность ходов...
		for (auto it = solution.begin(); it != solution.end(); it++) // Для каждой расстановки решения от начальной до целевой
		{
			// Записать "----" в следующей строке после предыдущей расстановки в выходной файл и перейти на следующую строку, если текущая расстановка не является начальной
			if (it != solution.cbegin())
				outputFile << "----" << std::endl;

			// Вывести текущую расстановку в выходной файл
			for (auto row : it->getField()) {
				for (auto symbol : row)
					outputFile << symbol;
				outputFile << std::endl;
			}
		}
	}

	// Вывести все возникшие ошибки в консоль...
	for (const auto& error : errors) // Для каждой ошибки
	{
		// #Получить текущую ошибку в строковом формате#
		string convertedError = error.convert();

		// Вывести текущую ошибку в консоль
		std::cout << convertedError << std::endl << std::endl;

		if (outputFile)
			outputFile << convertedError << std::endl << std::endl;
	}

	// Закрыть выходной файл
	if (outputFile)
		outputFile.close();
}
