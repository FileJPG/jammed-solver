/*!
* \file
* \brief ������ ���� �������� ������� ������� ��������� JammedSolver.
*
* \mainpage ������������ ��� ��������� "JammedSolver"
��������� ������������� ��� ������������� ������� ���� "��������".
��� ���������������� ��������� ���������� ������������ ������� Windows 7 ��� ����.
��������� ����������� �� ����� �++ � �������������� ����������� ���������.
��������� ������ �������� ��� ��������� ��������� ������: ��� �������� ����� � ��� ��������� ����� � ������� 'txt'.

������ ������� ������� ���������:
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
    // �������� ��������� �������� ����� � �������
	setlocale(LC_ALL, "Russian");

	// ������ ���������� � ��������� ����������
	if (argc != 3) {
		std::cout << "������: ��������� ��������� ��� ���������: '<���� � ���������> <���� � �������� �����> <���� � ��������� �����>'" << std::endl;
		return 0;
	}

	GameFieldData startField; // ��������� �����������
	GameFieldData goalField; // ������� �����������
	vector<Error> errors; // ����� ��������� ������ ��� ������ ���������

	// #��������� ������ �� �������� �����# � �������� ������, ���� ���� �� �����������
	vector<string> data; // ������ �� �������� �����
	bool fileOpened = readFile(argv[1], data);

	if (!fileOpened)
		errors.push_back(Error(cantOpenReadFile, argv[1]));

	// ��������� ��������� � ������� ����������� �����...
	if (fileOpened) // ���� ������� ������� ������� ����
	{
		// #������������� ����������� �� ����� ������ � �����������#
		vector<vector<string>> rawFields = parseText(data, FIELDS_SEPARATOR);
		
		vector<Field> fields; // ����������� � ������� ������� �����
		for (const auto& rawField : rawFields)
			fields.push_back(GameFieldData::convert(rawField));

		// �������� ������, ���� ��������� ��� ������� ����������� �� �������
		if (fields.size() < 2)
			errors.push_back(Error(incorrectFieldsCount, "", true, fields.size()));

		for (int i = 0; i < fields.size() && i < 2; i++) // ��� ������ ����������� (��������� � �������)
		{
			// �������� ������ ������� �����������, ���� #��� �� ��������#
			vector<Error> fieldErrors = GameFieldData::validate(fields[i]);

			for (auto& fieldError : fieldErrors)
				fieldError.isInitialField = i == 0 ? true : false;

			// �������� ������ ������� �����������, ���� ��� ����� ������������ ������
			if (fields[i].size() != FIELD_HEIGHT || fields[i][0].size() != FIELD_LENGTH)
				errors.push_back(Error(incorrectFieldSize, "", i == 0 ? true : false, 0, Size{ static_cast<int>(fields[i].size()), static_cast<int>(fields[i][0].size()) } ));
		}

		// �������� ������, ���� ������� ��� �����������, � #��� ����� ������ ����� �����#
		if (fields.size() >= 2) 
		{
			// ������� ����������� � ������ �������
			startField.setField(fields[0]);
			goalField.setField(fields[1]);

			// �������� ������
			if (!GameFieldData::compareSets(startField, goalField))
				errors.push_back(Error(differentSymbolsSets));
		}
	}
	
	// ��������� ��������� � �������� ������ � �������� ����...
	
	// ...������� �������� ���� � �������� ������, ���� ���� �� ���������
	std::ofstream outputFile(argv[2]);
	if (!outputFile)
		errors.push_back(Error(cantCreateFile, argv[2]));

	if (errors.empty()) // ���� �� ��������� ������ ��� ������ ����������� � �������� ��������� �����
	{
		// #������ ����#
		vector<GameFieldData> solution = solveJammed(startField, goalField);

		// ������� ���������� �������, ���� � ���� ��� �������...
		if (solution.empty()) // ���� ������� ���
		{
			// �������� "��� �������" � �������� ����
			outputFile << "��� �������" << std::endl;

			// ��������� ���������
			return 0;
		}

		// ������� � �������� ���� ���������� ����� �� ��������� ����������� � ������� � ��������� ������
		outputFile << solution.size() - 1 << std::endl << std::endl;

		// ������� � �������� ���� ������������������ �����...
		for (auto it = solution.begin(); it != solution.end(); it++) // ��� ������ ����������� ������� �� ��������� �� �������
		{
			// �������� "----" � ��������� ������ ����� ���������� ����������� � �������� ���� � ������� �� ��������� ������, ���� ������� ����������� �� �������� ���������
			if (it != solution.cbegin())
				outputFile << "----" << std::endl;

			// ������� ������� ����������� � �������� ����
			for (auto row : it->getField()) {
				for (auto symbol : row)
					outputFile << symbol;
				outputFile << std::endl;
			}
		}
	}

	// ������� ��� ��������� ������ � �������...
	for (const auto& error : errors) // ��� ������ ������
	{
		// #�������� ������� ������ � ��������� �������#
		string convertedError = error.convert();

		// ������� ������� ������ � �������
		std::cout << convertedError << std::endl << std::endl;

		if (outputFile)
			outputFile << convertedError << std::endl << std::endl;
	}

	// ������� �������� ����
	if (outputFile)
		outputFile.close();
}
