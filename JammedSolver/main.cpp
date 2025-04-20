/*!
* \file
* \brief ������ ���� �������� ������� ������� ��������� JammedSolver.
*
* \mainpage ������������ ��� ��������� "JammedSolver"
��������� ������������� ��� ������������� ������� ���� "��������".
��� ���������������� ��������� ���������� ������������ ������� Windows 7 ��� ����.
��������� ����������� �� ����� �++ � �������������� ����������� ��������� C++.
��������� ������ �������� ��� ��������� ��������� ������: ��� �������� ����� � ��� ��������� ����� � ������� 'txt'.

������ ������� ������� ���������:
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
 * \brief ������� ������� ���������
 * \param [in] argc - ���������� ���������� ���������� ��������� ������
 * \param [in] argv - ��������� ��������� ������
 * \param [in] argv[0] - �������� ������� ���������
 * \param [in] argv[1] - ���� � �������� �����
 * \param [in] argv[2] - ���� � ��������� �����
 * \return 0 - ��������� ����������� ��� ����������
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
