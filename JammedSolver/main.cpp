/*!
* \file
* \brief Данный файл содержит главную функцию программы JammedSolver.
*
* \mainpage Документация для программы "JammedSolver"
Программа предназначена для осуществления решения игры "Пятнашки".
Для функционирования программы необходима операционная система Windows 7 или выше.
Программа разработана на языке С++ с использованием стандартных библиотек C++.
Программа должна получать два аргумента командной строки: имя входного файла и имя выходного файла в формате 'txt'.

Пример команды запуска программы:
* \code
./JammedSolver.exe ./input.txt ./output.txt
* \endcode

* \author Ivan Maltsev
* \date June 2025
* \version 1.0
*/

#include <iostream>
#include "Structure.h"
#include "JammedSolver.h"
#include "GameFieldData.h"
#include "PriorityQueue.h"
#include "Node.h"
#include "Error.h"

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
    GameFieldData startField({ 
        {'1', '2', '3', '4'}, 
        {'5', '6', '7', '#'} 
    });
    GameFieldData goalField({
        {'6', '1', '7', '#'},
        {'5', '4', '3', '2'}
    });

    vector<GameFieldData> solution = solveJammed(startField, goalField);

    for (const GameFieldData currentField : solution) {
        for (int i = 0; i < currentField.getSize().height; i++) {
            for (int j = 0; j < currentField.getSize().length; j++) {
                std::cout << currentField.getField()[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << solution.size() - 1 << std::endl;

    return 0;
}
