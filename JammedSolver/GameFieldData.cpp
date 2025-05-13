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

	int totalDistance = 0; // ...�������, ��� ������������� ���������� �� �������
	vector<vector<bool>> occupied(fieldSizeY, vector<bool>(fieldSizeX, false)); // ...�������, ��� �� ���� ����� ������� ����������� �� ��������� � ������� � ������� �����������

	for (int y1 = 0; y1 < fieldSizeY; y1++) { // ��� ������ ����� ������� �����������
		for (int x1 = 0; x1 < fieldSizeX; x1++) {
			if (field[y1][x1] == '#') continue;

			Position bestPos; // ����������� �������
			int minDistance = INT_MAX; // ����������� ������������� ����������

			// ����� ��������� ��������� ������� ������� ��� ������� �����...
			for (int y2 = 0; y2 < fieldSizeY; y2++) { // ��� ������ ��������� ������� ������� ����������� ��� ������� �����
				for (int x2 = 0; x2 < fieldSizeX; x2++) {
					if (!occupied[y2][x2] && field[y1][x1] == goalField.field[y2][x2]) {
						// ��������� ������������� ���������� �� ��������������� ����� �� ������� �������
						int currentDistance = abs(y1 - y2) + abs(x1 - x2); // ������� ���������� �� ����� �� ������� �������

						// ��� ��������������� ����� ��������� ������� �������, ���� ���������� �� ����� �� ������� ������� �����������
						if (currentDistance < minDistance) {
							// �������� ����������� ����������
							minDistance = currentDistance;

							// ��������� ����� ������� � �����
							bestPos = {x2, y2};
						}
					}
				}
			}
			if (minDistance != INT_MAX) {
				// ��������� ������������� ���������� �� ������� ����� �� ��������� ������� ������� � ��������� ��� � ����������
				totalDistance += minDistance;

				// ��������� ������� � �����
				occupied[bestPos.y][bestPos.x] = true;
			}
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

	for (int y = 0; y < fieldSize.height; y++) // ��� ������ ������ �����������
		for (int x = 0; x < fieldSize.length; x++) // ��� ������ ������ ������� ������
			// �������� ������� ������� ������ � �������������� ������, ���� �� �������� ��������� � ��������
			if (field[y][x] == value) positions.push_back({ x, y });

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
