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
};

/*!
* \brief Размер
*/
struct Size
{
    int lenght; // Длина
    int height; // Высота
};
