/*!
* \file
* \brief Данный файл является заголовочным файлом для класса GameFieldData
*/

#pragma once

#include <vector>

#include "Structure.h"
#include "Error.h"

using std::vector;

using Field = vector<vector<char>>; // Псевдоним для игрового поля

/*!
 * \brief Игровое поле с дополнительными данными
 */
class GameFieldData
{
    Field field; // Игровое поле

    int numberOfMoves; // Количество сделанных ходов

    int manhattanDistance; // Манхэттенское расстояние

public:

    /*!
    * \brief Проверить расстановку фишек на валидность
    * \param [in] field - расстановка
    * \return Ошибки в расстановке
    */
    static vector<Error> validate(const Field& field);

    /*!
    * \brief Сравнить расстановки фишек
    * \param [in] firstField - первая расстановка
    * \param [in] secondField - вторая расстановка
    * \return Расстановки являются одинаковыми
    */
    static bool compareFields(const GameFieldData& firstField, const GameFieldData& secondField);

    /*!
    * \brief Сравнить наборы фишек в расстановках
    * \param [in] firstField - первая расстановка
    * \param [in] secondField - вторая расстановка
    * \return Расстановки имеют одинаковый набор фишек
    */
    static bool compareSets(const GameFieldData& firstField, const GameFieldData& secondField);

    /*!
    * \brief Получить размер расстановки
    * \return Размер расстановки по горизонтали и вертикали
    */
    Size getSize() const;

    /*!
    * \brief Создать возможные ходы для расстановки
    * \return Все возможные ходы
    */
    vector<GameFieldData> getMoves() const;

    /*! Вычислить манхэттенское расстояние до расстановки фишек
    * \param [in] goalField - целевая расстановка
    * \return Манхэттенское расстояние для всех фишек
    */
    int getManhattanDistance(const GameFieldData& goalField) const;

    /*!
    * \brief Переместить фишку на пустую клетку
    * \param [in] direction - направление перемещения пустой клетки
    * \return Перемещение успешно
    */
    bool swap(const Direction& direction);

private:

    /*!
    * \brief Получить позиции клетки в расстановке
    * \param [in] value - значение нужной клетки
    * \return Позиции нужной клетки
    */
    vector<Position> getPos(const char& value) const;
};
