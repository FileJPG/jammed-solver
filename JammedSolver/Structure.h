/*!
* \file
* \brief Данный файл является заголовочным файлом для дополнительных структур и перечислений
*/

#pragma once

/*!
* \brief Направление
*/
enum Direction
{
    up, // Вверх
    down, // Вниз
    right, // Вправо
    left // Влево
};

/*!
* \brief Позиция
*/
struct Position
{
    int x; // Координата по горизонтали
    int y; // Координата по вертикали

    /*!
    * \brief Оператор ==
    */
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
};

/*!
* \brief Размер
*/
struct Size
{
    int length; // Длина
    int height; // Высота

    /*!
    * \brief Оператор ==
    */
    bool operator==(const Size& other) const { return length == other.length && height == other.height; }

    /*!
    * \brief Оператор !=
    */
    bool operator!=(const Size& other) const { return !operator==(other); }

    /*!
    * \brief Получить площадь
    * \return Площадь для данных размеров
    */
    int square() const { return length * height; }

    /*!
    * \brief Сравнить размеры
    * \param [in] other - другой размер
    * \return Размеры одинаковые
    */
    bool compare(const Size& other) const { return operator==(other); }
};
