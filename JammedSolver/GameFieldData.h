#pragma once

#include <vector>
#include <string>

using std::vector;

// ������� ���� � ������������ � ��������������� �������
class GameFieldData
{
    // ������� ����
    vector<vector<char>> field;

    // ���������� ��������� �����
    int numberOfMoves;
};
