/*!
* \file
* \brief ������ ���� �������� � ���� ���������� ������� ������ GameFieldData
*/

#include <unordered_set>
#include "GameFieldData.h"

using std::unordered_set;
using std::unordered_multiset;

GameFieldData::GameFieldData(const Field& field, const int& numberOfMoves, const int& manhattanDistance)
{
	this->field = validate(field).empty() ? field : DEFAULT_FIELD;
	this->numberOfMoves = numberOfMoves;
	this->manhattanDistance = manhattanDistance;
}

bool GameFieldData::operator==(const GameFieldData& other) { return getField() == other.getField(); }

bool GameFieldData::setField(Field newField)
{
	if (validate(newField).empty()) {
		this->field = newField;
		return true;
	}
	return false;
}

Field GameFieldData::getField() const { return field; }

Size GameFieldData::getSize() const { return { static_cast<int>(field[0].size()), static_cast<int>(field.size()) }; }

int GameFieldData::getNumberOfMoves() const { return numberOfMoves; }

int GameFieldData::getManhattanDistance() const { return manhattanDistance; }

void GameFieldData::setNumberOfMoves(const int& value) { numberOfMoves = value; }

void GameFieldData::setManhattanDistance(const int& value) { manhattanDistance = value; }

vector<Error> GameFieldData::validate(const Field& field)
{
	vector<Error> errors; // ��������� ������

	// ��������� ����������� �� ������������� �����...
	// ������� ������, ���� ����������� ������
	if (field.empty()) {
		errors.push_back(Error(incorrectFieldForm));
		return errors;
	}

	for (const auto& row : field) // ��� ������ ������ �����������
	{
		// �������� ������, ���� ����� ������� ������ ����������� ���������� �� ����� ������ ������
		if (row.size() != field[0].size()) {
			errors.push_back(Error(incorrectFieldForm));
			break;
		}
	}

	// ��������� ������ �����������...
	int emptyCellCount = 0; // ...�������, ��� ������� ������ ������ ����� ����

	vector<char> fieldSymbols; // ...�������� ����� �������� �����������
	for (const auto& row : field)
		fieldSymbols.insert(fieldSymbols.end(), row.begin(), row.end());

	Error errorIncorrectSymbols(incorrectSymbolsInField);
	for (const auto& fieldSymbol : fieldSymbols) // ��� ������ ������ �����������
	{
		// ���������������� ������� ������ ������, ���� ������� ������ �������� ������
		if (fieldSymbol == '#')
			emptyCellCount++;

		// �������� ������ � ������, ���� ������� ������ �� �������� ���������� ��� ������
		if (!isalnum(fieldSymbol) && fieldSymbol != '#')
			errorIncorrectSymbols.str.push_back(fieldSymbol);
	}

	// �������� ������, ���� � ����������� �� ���� ������ ������
	if (emptyCellCount != 1)
		errors.push_back(Error(incorrectEmptyCellsCount, "", true, emptyCellCount));

	// �������� ������, ���� ���� ���� �� ���� ������������ ������
	if (!errorIncorrectSymbols.str.empty())
		errors.push_back(errorIncorrectSymbols);

	// ������� ��������� ������
	return errors;
}

bool GameFieldData::isSolvable(const GameFieldData& startField, const GameFieldData& goalField)
{
	// �������, ��� ���� ���������, ���� #������ ����� ����� ������#
	if (!GameFieldData::compareSets(startField, goalField)) 
		return false;

	// �������, ��� ���� �������, ���� � ������ ����� ����� ���� ���� �� ��� ���������� �����
	unordered_set<char> fieldSymbols; // ��������� �������� �����������
	for (const auto& row : startField.field)
		fieldSymbols.insert(row.cbegin(), row.cend());

	if (fieldSymbols.size() < startField.getSize().square())
		return true;

	// #��������� ���������� �������� ��� ��������� � ������� �����������#
	int firstInversionsCount = startField.countInversions();
	int secondInversionsCount = goalField.countInversions();

	// #��������� ������� ������ ������ ��� ��������� � ������� �����������#
	Position firstEmptyCellPos = startField.getPos('#')[0];
	Position secondEmptyCellPos = goalField.getPos('#')[0];

	// �������, ��� ���� �������, ���� �������� ����� �������� � ������ ������ � ������ ������� �� ������ ���� ��������� � ��������� �� ������
	return (firstInversionsCount + firstEmptyCellPos.y) % 2 == (secondInversionsCount + secondEmptyCellPos.y) % 2;
}

bool GameFieldData::compareFields(const GameFieldData& firstField, const GameFieldData& secondField)
{
	Size firstFieldSize = firstField.getSize(); // ������� ������ �����������
	Size secondFieldSize = secondField.getSize(); // ������� ������ �����������

	// ������� ������������� ���������, ���� #������� ����������� ������#
	if (firstFieldSize != secondFieldSize)
		return false;

	// �������� ������ �����������...
	for (int i = 0; i < firstFieldSize.height; i++) // ��� ������ ������� �����������
		for (int j = 0; j < firstFieldSize.length; j++)
			if (firstField.field[i][j] != secondField.field[i][j])
				return false; // ������� ������������� ���������, ���� ������ ����������� �� ������� ������� �� ���������

	// ������� ������������� ���������
	return true;
}

bool GameFieldData::compareSets(const GameFieldData& firstField, const GameFieldData& secondField)
{
	// ������� ������������� ���������, ���� #������� ����������� ������#
	if (firstField.getSize() != secondField.getSize())
		return false;

	// �������� ������ �������� �����������...
	std::unordered_multiset<char> firstSymbolsSet, secondSymbolsSet; // ��������� �������� �����������

	for (const auto& row : firstField.field) // ��� ������ ������ ����������� ����� �����
		firstSymbolsSet.insert(row.begin(), row.end()); // �������� � ��������� �������� ����������� ������� ������ ����������� ��������������

	for (const auto& row : secondField.field)
		secondSymbolsSet.insert(row.begin(), row.end());

	// ������� ��������� ��������� �������� �������� �����������
	return firstSymbolsSet == secondSymbolsSet;
}

Field GameFieldData::convert(const vector<string>& rawField)
{
	Field field; // ����������� � ����� �������

	for (const auto& rawRow : rawField)
	{
		vector<char> row; // ������ ����������� � ����� �������

		// �������� ������� ������� ������
		for (const auto& symbol : rawRow)
			row.push_back(symbol);

		// �������� ������� ������ � ����� �������
		field.push_back(row);
	}

	return field;
}

vector<GameFieldData> GameFieldData::getMoves() const
{
	Position emptyCellPos = getPos('#')[0]; // ...#��������� ������� ������ ������ � �����������#

	vector<GameFieldData> moves; // ...�������, ��� �������������� ������ � ������ ������������� ������

	vector<Direction> directions = {up, down, right, left}; // ����������� ��� �����

	for (const Direction& direction : directions) // ��� ������ �������� ����� ������ ������
	{
		// ������� ������� ����������� � � ��� #����������� ������� ����� �� ������ ������#
		GameFieldData currentMove(field, numberOfMoves + 1); // ������� ���

		bool isCurrentMoveValid = currentMove.swap(direction);

		// �������� ����� ����������� � �������������� ������, ���� ������� ��� ��������
		if (isCurrentMoveValid) 
			moves.push_back(currentMove);
	}

	// ������� ������ � ���������� �������������
	return moves;
}

int GameFieldData::getManhattanDistance(const GameFieldData& goalField) const
{
	int fieldSizeX = getSize().length; // ����� ����
	int fieldSizeY = getSize().height; // ������ ����

	int totalDistance = 0; // ...�������, ��� ������������� ���������� �� �������

	vector<vector<bool>> occupied(fieldSizeY, vector<bool>(fieldSizeX, false)); // ...�������, ��� �� ���� ����� ������� ����������� �� ��������� � ������� � ������� �����������

	for (int y1 = 0; y1 < fieldSizeY; y1++) { // ��� ������ ����� ������� �����������
		for (int x1 = 0; x1 < fieldSizeX; x1++) {
			if (field[y1][x1] == '#') continue;

			Position bestPos; // ����� �������� ������� ������� ��� ������� �����
			int minDistance = INT_MAX; // ������������� ���������� �� ����� �������� ������� �������

			// ����� ��������� ��������� ������� ������� ��� ������� �����...
			for (int y2 = 0; y2 < fieldSizeY; y2++) { // ��� ������ ��������� ������� ������� ����������� ��� ������� �����
				for (int x2 = 0; x2 < fieldSizeX; x2++) {
					if (!occupied[y2][x2] && field[y1][x1] == goalField.field[y2][x2])
					{
						// ��������� ������������� ���������� �� ��������������� ����� �� ������� �������
						int currentDistance = abs(y1 - y2) + abs(x1 - x2);

						// ��� ��������������� ����� ��������� ������� �������, ���� ���������� �� ����� �� ������� ������� �����������
						if (currentDistance < minDistance)
						{
							// �������� ����������� ����������
							minDistance = currentDistance;

							// �������� ����� �������� ������� ������� �����
							bestPos = {x2, y2};
						}
					}
				}
			}
			// ��������� ������������� ���������� �� ������� ����� �� ��������� ������� ������� � ��������� ��� � ����������
			totalDistance += minDistance;

			// ��������� ������� � �����
			occupied[bestPos.y][bestPos.x] = true;
		}
	}
	// ������� ����� ������������� ���������� �� ���� ����� ������� ����������� �� �� ������� �������
	return totalDistance;
}

bool GameFieldData::swap(const Direction& direction)
{
	// #�������� ������� ������ ������#
	Position emptyCellPos = getPos('#')[0];

	// �������� ������� ������ �����, ������ �� ��������� �����������
	Position neighborPos = emptyCellPos; // ������� �������� �����
	switch (direction) {
		case up:	neighborPos.y--; break;
		case down:	neighborPos.y++; break;
		case right: neighborPos.x++; break;
		case left:	neighborPos.x--; break;
	}

	// ������� ������������� ���������, ���� ������� ����� ������� �� ����� ����
	if (neighborPos.x < 0 || neighborPos.x >= getSize().length || neighborPos.y < 0 || neighborPos.y >= getSize().height)
		return false;

	// ����������� ������ ����� �� ������� ������ ������
	field[emptyCellPos.y][emptyCellPos.x] = field[neighborPos.y][neighborPos.x];

	// ����������� ������ ������ �� ������� ������ �����
	field[neighborPos.y][neighborPos.x] = '#';

	// ������� ������������� ���������
	return true;
}

vector<Position> GameFieldData::getPos(const char& value) const
{
	Size fieldSize = getSize(); // ������� ����
	vector<Position> positions; // ...�������, ��� �������������� ������ ������

	for (int y = 0; y < fieldSize.height; y++) // ��� ������ ������ �����������
		for (int x = 0; x < fieldSize.length; x++) // ��� ������ ������ ������� ������
			if (field[y][x] == value) 
				positions.push_back({ x, y }); // �������� ������� ������� ������ � �������������� ������, ���� �� �������� ��������� � ��������

	// ������� �������������� ������
	return positions;
}

int GameFieldData::countInversions() const
{
	int inversionsCount = 0; // ...�������, ��� ���������� �������� ����� ����

	vector<char> fieldSymbols; // ������ �������� ����
	for (const auto& row : this->field) 
		fieldSymbols.insert(fieldSymbols.end(), row.begin(), row.end());

	for (int i = 0; i < fieldSymbols.size(); i++) // ��� ������� ������� �����������
		for (int j = i + 1; j < fieldSymbols.size(); j++) // ��� ������� ������� ����������� ����� ��������
			if (fieldSymbols[i] != '#' && fieldSymbols[j] != '#' && fieldSymbols[i] > fieldSymbols[j]) 
				inversionsCount++; // ���������������� ���������� ��������, ���� ������� ������ ������ ������������ �� �������

	// ������� ���������� ��������
	return inversionsCount;
}
