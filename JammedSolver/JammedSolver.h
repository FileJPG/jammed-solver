/*!
* \file
* \brief Данный файл является заголовочным файлом для программы
*/

#pragma once

#include <vector>
#include <string>

#include "GameFieldData.h"
#include "Error.h"

using std::vector;
using std::string;

/*!
* \brief Прочитать данные из файла построчно
* \param [in] filePath - путь к входному файлу
* \param [out] data - прочитанные данные
* \return Файл успешно открыт
*/
bool readFile(const string& filePath, vector<string>& data);

/*!
* \brief Разделить текст на блоки строкой-разделителем
* \param [in] text - текст
* \param [in] separator - строка-разделитель
* \return Блоки текста
*/
vector<vector<string>> parseText(const vector<string>& text, const string& separator);

/*!
* \brief Решить игру "Jammed"
* \param [in] startField - начальная расстановка фишек
* \param [in] goalField - целевая расстановка фишек
* \return Последовательность расстановок от начальной до целевой. Пустой вектор, если решения нет
*/
vector<GameFieldData> solveJammed(const GameFieldData& startField, const GameFieldData& goalField);
