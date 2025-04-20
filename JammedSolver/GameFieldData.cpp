/*!
* \file
* \brief ������ ���� �������� � ���� ���������� ������� ������ GameFieldData
*/

#include <unordered_set>
#include "GameFieldData.h"

using std::unordered_multiset;

GameFieldData::GameFieldData(const Field& field, const int& numberOfMoves, const int& manhattanDistance)
{
	this->field = validate(field).empty() ? field : DEFAULT_FIELD;
	this->numberOfMoves = numberOfMoves;
	this->manhattanDistance = manhattanDistance;
}

bool GameFieldData::operator==(const GameFieldData& other) { return getField() == other.getField(); }

Field GameFieldData::getField() const { return field; }

Size GameFieldData::getSize() const { return { static_cast<int>(field[0].size()), static_cast<int>(field.size()) }; }

int GameFieldData::getNumberOfMoves() const { return numberOfMoves; }

int GameFieldData::getManhattanDistance() const { return manhattanDistance; }

void GameFieldData::setNumberOfMoves(const int& value) { numberOfMoves = value; }

void GameFieldData::setManhattanDistance(const int& value) { manhattanDistance = value; }

vector<Error> GameFieldData::validate(const Field& field)
{
	return {};
}

bool GameFieldData::isSolvable(const GameFieldData& startField, const GameFieldData& goalField)
{
	// �������, ��� ���� ���������, ���� #������ ����� ����� ������#
	if (!GameFieldData::compareSets(startField, goalField)) return false;

	// �������, ��� ���� �������, ���� � ������ ����� ����� ���� ���� �� ��� ���������� �����
	vector<char> fieldSymbols; // ��������� ������ ��������� �����������
	for (const auto& row : startField.field) fieldSymbols.insert(fieldSymbols.end(), row.begin(), row.end());
	for (const char& symbol : fieldSymbols)
		if (std::count(fieldSymbols.cbegin(), fieldSymbols.cend(), symbol) > 1)
			return true;

	// #��������� ���������� �������� ��� ��������� � ������� �����������#
	int firstInversionsCount = startField.countInversions();
	int secondInversionsCount = goalField.countInversions();

	// #��������� ������� ������ ������ ��� ��������� � ������� �����������#
	vector<Position> firstEmptyCellPos = startField.getPos('#');
	vector<Position> secondEmptyCellPos = goalField.getPos('#');

	// �������, ��� ���� �������, ���� �������� ����� �������� � ������ ������ � ������ ������� �� ������ ���� ��������� � ��������� �� ������
	return (firstInversionsCount + firstEmptyCellPos[0].y) % 2 == (secondInversionsCount + secondEmptyCellPos[0].y) % 2;
}

bool GameFieldData::compareFields(const GameFieldData& firstField, const GameFieldData& secondField)
{
	// ������� ������������� ���������, ���� #������� ����������� ������#
	if (!firstField.getSize().compare(secondField.getSize()))
		return false;

	// �������� ������ �����������...
	// ��� ������ ������� �����������
	for (int i = 0; i < firstField.getSize().height; i++)
		for (int j = 0; j < firstField.getSize().length; j++)
			// ������� ������������� ���������, ���� ������ ����������� �� ������� ������� �� ���������
			if (firstField.getField()[i][j] != secondField.getField()[i][j])
				return false;

	// ������� ������������� ���������
	return true;
}

bool GameFieldData::compareSets(const GameFieldData& firstField, const GameFieldData& secondField)
{
	// ������� ��������� ���������, ���� #����������� ������� �������#
	if (firstField.getSize() != secondField.getSize())
		return false;

	// �������� ������ �������� �����������...
	std::unordered_multiset<char> firstSymbols, secondSymbols; // �������, ��� ������ �������� ����������� ������
	for (const auto& row : firstField.getField()) // ��� ������ ������ ����������� ����� �����
		firstSymbols.insert(row.begin(), row.end()); // �������� � ������ �������� ����������� ������� ������ ����������� ��������������
	for (const auto& row : secondField.getField())
		secondSymbols.insert(row.begin(), row.end());

	// ������� ��������� ��������� ������� �������� �����������
	return firstSymbols == secondSymbols;
}

vector<GameFieldData> GameFieldData::getMoves() const
{
	// ...#��������� ������� ������ ������ � �����������#
	Position emptyCellPos = getPos('#')[0];

	// ...�������, ��� �������������� ������ � ������ ������������� ������
	vector<GameFieldData> moves;

	vector<Direction> directions = {up, down, right, left}; // ����������� ��� �����
	for (const Direction& direction : directions) { // ��� ������ �������� ����� ������ ������
		// ������� ������� ����������� � � ��� #����������� ������� ����� �� ������ ������#
		GameFieldData currentMove(field, numberOfMoves + 1); // ������� ���

		bool isCurrentMoveValid = currentMove.swap(direction);

		// �������� ����� ����������� � �������������� ������, ���� ������� ��� ��������
		if (isCurrentMoveValid) moves.push_back(currentMove);
	}

	// ������� ������ � ���������� �������������
	return moves;
}

int GameFieldData::getManhattanDistance(const GameFieldData& goalField) const
{
	int fieldSizeX = getSize().length; // ����� ����
	int fieldSizeY = getSize().height; // ������ ����

	int manhattanDistance = 0; // ...�������, ��� ������������� ���������� �� �������
	vector<vector<bool>> map(fieldSizeY, vector<bool>(fieldSizeX, false)); // ...�������, ��� �� ���� ����� ������� ����������� �� ��������� � ������� � ������� �����������

	// ��� ������ ����� ������� �����������
	for (int i = 0; i < fieldSizeY; i++) {
		for (int j = 0; j < fieldSizeX; j++) {
			if (field[i][j] == '#') continue;

			Position lastPos = { -1, -1 }; // ���������� ����������� �������
			int minManhattanDistance = 10e+9; // ���������� ������������� ����������
			int currentManhattanDistance = 0; // ������� ���������� �� ����� �� ������� �������

			// ����� ��������� ��������� ������� ������� ��� ������� �����...
			for (int k = 0; k < fieldSizeY; k++) { // ��� ������ ��������� ������� ������� ����������� ��� ������� �����
				for (int l = 0; l < fieldSizeX; l++) {
					if (map[k][l] == false && field[i][j] == goalField.field[k][l]) {
						// ��������� ������������� ���������� �� ��������������� ����� �� ������� �������
						int currentManhattanDistance = fabs(i - k) + fabs(j - l);

						// ��� ��������������� ����� �������� ���������� � ��������� ������� �������, ���� ���������� �� ����� �� ������� ������� �����������
						if (currentManhattanDistance < minManhattanDistance) {
							minManhattanDistance = currentManhattanDistance; // �������� ����������� ����������

							if (lastPos.x != -1) map[lastPos.y][lastPos.x] = false; // �������� ������ ������� �� �����

							map[k][l] = true; // ��������� ����� ������� � �����
						}
					}
				}
			}
			// ��������� ������������� ���������� �� ������� ����� �� ��������� ������� ������� � ��������� ��� � ����������
			manhattanDistance += minManhattanDistance;
		}
	}
	// ������� ����� ������������� ���������� �� ���� ����� ������� ����������� �� �� ������� �������
	return manhattanDistance;
}

bool GameFieldData::swap(const Direction& direction)
{
	// #�������� ������� ������ ������#
	Position emptyCellPos = getPos('#')[0];

	// �������� ������� ������ �����, ������ �� ��������� �����������
	Position neighborPos = emptyCellPos; // ������� ������ �������� �����
	switch (direction) {
		case up: neighborPos.y--; break;
		case down: neighborPos.y++; break;
		case right: neighborPos.x++; break;
		case left: neighborPos.x--; break;
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

	for (int i = 0; i < fieldSize.height; i++) // ��� ������ ������ �����������
		for (int j = 0; j < fieldSize.length; j++) // ��� ������ ������ ������� ������
			// �������� ������� ������� ������ � �������������� ������, ���� �� �������� ��������� � ��������
			if (field[i][j] == value) positions.push_back({ j, i });

	// ������� �������������� ������
	return positions;
}

int GameFieldData::countInversions() const
{
	int inversionsCount = 0; // ...�������, ��� ���������� �������� ����� ����
	vector<char> symbols; // ������ �������� ����
	for (const auto& row : this->field) symbols.insert(symbols.end(), row.begin(), row.end());

	for (int i = 0; i < symbols.size(); i++) // ��� ������� ������� �����������
		for (int j = i + 1; j < symbols.size(); j++) // ��� ������� ������� ����������� ����� ��������
			// ���������������� ���������� ��������, ���� ������� ������ ������ ������������ �� �������
			if (symbols[i] != '#' && symbols[j] != '#' && symbols[i] > symbols[j]) inversionsCount++;

	// ������� ���������� ��������
	return inversionsCount;
}
