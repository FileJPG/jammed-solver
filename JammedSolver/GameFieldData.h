#pragma once

#include <vector>
#include <string>

using std::vector;

// Игровое поле с расстановкой и дополнительными данными
class GameFieldData
{
    // Игровое поле
    vector<vector<char>> field;

    // Количество сделанных ходов
    int numberOfMoves;
};
