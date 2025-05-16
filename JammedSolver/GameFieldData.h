/*!
* \file
* \brief Данный файл является заголовочным файлом для класса GameFieldData
*/

#pragma once

#include <vector>
#include "Structure.h"
#include "Error.h"

using std::vector;

using Field = vector<vector<char>>; //!< Псевдоним для игрового поля

const Field DEFAULT_FIELD = { {'#'} }; //!< Поле по умолчанию

/*!
 * \brief Игровое поле с дополнительными данными
 */
class GameFieldData
{
    friend vector<GameFieldData> solveJammed(const GameFieldData& startField, const GameFieldData& goalField);

    Field field; //!< Игровое поле

    int numberOfMoves; //!< Количество сделанных ходов

    int manhattanDistance; //!< Манхэттенское расстояние

public:

    /*!
    * \brief Конструктор с параметрами
    */
    GameFieldData(const Field& field = DEFAULT_FIELD, const int& numberOfMoves = 0, const int& manhattanDistance = -1);

    /*!
    * \brief Оператор ==
    */
    bool operator==(const GameFieldData& other);

    /*!
    * \brief Сеттер для поля field
    */
    bool setField(Field newField);

    /*!
    * \brief Геттер для поля field
    */
    Field getField() const;

    /*!
    * \brief Геттер для размеров расстановки
    */
    Size getSize() const;

    /*!
    * \brief Геттер для поля numberOfMoves
    */
    int getNumberOfMoves() const;

    /*!
    * \brief Геттер для поля manhattanDistance
    */
    int getManhattanDistance() const;

    /*!
    * \brief Сеттер для количества сделанных ходов
    */
    void setNumberOfMoves(const int& value);

    /*!
    * \brief Сеттер для поля manhattanDistance
    */
    void setManhattanDistance(const int& value);

    /*!
    * \brief Проверить расстановку фишек на валидность
    * \param [in] field - расстановка
    * \return Ошибки в расстановке
    */
    static vector<Error> validate(const Field& field);

    /*!
    * \brief Доказать решаемость игры
    * \param [in] startField - начальная расстановка
    * \param [in] goalField - целевая расстановка
    * \return Целевая расстановка является достижимой из начальной
    */
    static bool isSolvable(const GameFieldData& startField, const GameFieldData& goalField);

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
    * \brief Преобразовать формат расстановки
    * \param [in] rawField - расстановка в формате vector<string>
    * \return Расстановка в формате Field
    */
    static Field convert(const vector<string>& rawField);

    /*!
    * \brief Создать возможные ходы для расстановки
    * \return Все возможные ходы
    */
    vector<GameFieldData> getMoves() const;

    /*!
    * \brief Вычислить манхэттенское расстояние до расстановки фишек
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

    /*!
    * \brief Получить позиции клетки в расстановке
    * \param [in] value - значение нужной клетки
    * \return Позиции нужной клетки
    */
    vector<Position> getPos(const char& value) const;

    /*!
    * \brief Посчитать количество инверсий в расстановке
    * \return Количество инверсий в расстановке
    */
    int countInversions() const;
};
