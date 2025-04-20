/*!
* \file
* \brief Данный файл содержит в себе реализацию функций класса GameFieldData
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
	// Считать, что игра нерешаема, если #наборы фишек полей разные#
	if (!GameFieldData::compareSets(startField, goalField)) return false;

	// Считать, что игра решаема, если в наборе фишек полей есть хотя бы две одинаковые фишки
	vector<char> fieldSymbols; // Составить вектор элементов расстановки
	for (const auto& row : startField.field) fieldSymbols.insert(fieldSymbols.end(), row.begin(), row.end());
	for (const char& symbol : fieldSymbols)
		if (std::count(fieldSymbols.cbegin(), fieldSymbols.cend(), symbol) > 1)
			return true;

	// #Посчитать количество инверсий для начальной и целевой расстановок#
	int firstInversionsCount = startField.countInversions();
	int secondInversionsCount = goalField.countInversions();

	// #Вычислить позиции пустой клетки для начальной и целевой расстановок#
	vector<Position> firstEmptyCellPos = startField.getPos('#');
	vector<Position> secondEmptyCellPos = goalField.getPos('#');

	// Считать, что игра решаема, если четность суммы инверсии и номера строки с пустой клеткой на первом поле совпадает с четностью на втором
	return (firstInversionsCount + firstEmptyCellPos[0].y) % 2 == (secondInversionsCount + secondEmptyCellPos[0].y) % 2;
}

bool GameFieldData::compareFields(const GameFieldData& firstField, const GameFieldData& secondField)
{
	// Вернуть отрицательный результат, если #размеры расстановок разные#
	if (!firstField.getSize().compare(secondField.getSize()))
		return false;

	// Сравнить клетки расстановок...
	// Для каждой позиции расстановки
	for (int i = 0; i < firstField.getSize().height; i++)
		for (int j = 0; j < firstField.getSize().length; j++)
			// Вернуть отрицательный результат, если клетки расстановок на текущей позиции не совпадают
			if (firstField.getField()[i][j] != secondField.getField()[i][j])
				return false;

	// Вернуть положительный результат
	return true;
}

bool GameFieldData::compareSets(const GameFieldData& firstField, const GameFieldData& secondField)
{
	// Вернуть ошибочный результат, если #расстановки разного размера#
	if (firstField.getSize() != secondField.getSize())
		return false;

	// Получить наборы символов расстановок...
	std::unordered_multiset<char> firstSymbols, secondSymbols; // Считать, что наборы символов расстановок пустые
	for (const auto& row : firstField.getField()) // Для каждой строки расстановки обоих полей
		firstSymbols.insert(row.begin(), row.end()); // Вставить в наборы символов расстановок текущие строки расстановок соответственно
	for (const auto& row : secondField.getField())
		secondSymbols.insert(row.begin(), row.end());

	// Вернуть результат сравнения наборов символов расстановок
	return firstSymbols == secondSymbols;
}

vector<GameFieldData> GameFieldData::getMoves() const
{
	// ...#Вычислить позицию пустой клетки в расстановке#
	Position emptyCellPos = getPos('#')[0];

	// ...Считать, что результирующий вектор с новыми расстановками пустой
	vector<GameFieldData> moves;

	vector<Direction> directions = {up, down, right, left}; // Направления для ходов
	for (const Direction& direction : directions) { // Для каждой соседней фишки пустой клетки
		// Создать текущую расстановку и в ней #переставить текущую фишку на пустую клетку#
		GameFieldData currentMove(field, numberOfMoves + 1); // Текущий ход

		bool isCurrentMoveValid = currentMove.swap(direction);

		// Положить новую расстановку в результирующий вектор, если текущий ход валидный
		if (isCurrentMoveValid) moves.push_back(currentMove);
	}

	// Вернуть вектор с созданными расстановками
	return moves;
}

int GameFieldData::getManhattanDistance(const GameFieldData& goalField) const
{
	int fieldSizeX = getSize().length; // Длина поля
	int fieldSizeY = getSize().height; // Высота поля

	int manhattanDistance = 0; // ...Считать, что манхэттенское расстояние не найдено
	vector<vector<bool>> map(fieldSizeY, vector<bool>(fieldSizeX, false)); // ...Считать, что ни одна фишка текущей расстановки не привязана к позиции в целевой расстановке

	// Для каждой фишки текущей расстановки
	for (int i = 0; i < fieldSizeY; i++) {
		for (int j = 0; j < fieldSizeX; j++) {
			if (field[i][j] == '#') continue;

			Position lastPos = { -1, -1 }; // Предыдущая привязанная позиция
			int minManhattanDistance = 10e+9; // Предыдущее манхэттенское расстояние
			int currentManhattanDistance = 0; // Текущее расстояние от фишки до целевой позиции

			// Найти ближайшую незанятую целевую позицию для текущей фишки...
			for (int k = 0; k < fieldSizeY; k++) { // Для каждой незанятой целевой позиции расстановки для текущей фишки
				for (int l = 0; l < fieldSizeX; l++) {
					if (map[k][l] == false && field[i][j] == goalField.field[k][l]) {
						// Посчитать манхэттенское расстояние от рассматриваемой фишки до текущей позиции
						int currentManhattanDistance = fabs(i - k) + fabs(j - l);

						// Для рассматриваемой фишки отвязать предыдущую и привязать текущую позицию, если расстояние от фишки до текущей позиции минимальное
						if (currentManhattanDistance < minManhattanDistance) {
							minManhattanDistance = currentManhattanDistance; // Изменить минимальное расстояние

							if (lastPos.x != -1) map[lastPos.y][lastPos.x] = false; // Отвязать старую позицию от фишки

							map[k][l] = true; // Привязать новую позицию к фишке
						}
					}
				}
			}
			// Посчитать манхэттенское расстояние от текущей фишки до найденной целевой позиции и прибавить его к результату
			manhattanDistance += minManhattanDistance;
		}
	}
	// Вернуть сумму манхэттенских расстояний от всех фишек текущей расстановки до их целевых позиций
	return manhattanDistance;
}

bool GameFieldData::swap(const Direction& direction)
{
	// #Получить позицию пустой клетки#
	Position emptyCellPos = getPos('#')[0];

	// Получить позицию нужной фишки, исходя из заданного направления
	Position neighborPos = emptyCellPos; // Позиция нужной соседней фишки
	switch (direction) {
		case up: neighborPos.y--; break;
		case down: neighborPos.y++; break;
		case right: neighborPos.x++; break;
		case left: neighborPos.x--; break;
	}

	// Вернуть отрицательный результат, если позиция фишки выходит за рамки поля
	if (neighborPos.x < 0 || neighborPos.x >= getSize().length || neighborPos.y < 0 || neighborPos.y >= getSize().height)
		return false;

	// Скопировать нужную фишку на позицию пустой клетки
	field[emptyCellPos.y][emptyCellPos.x] = field[neighborPos.y][neighborPos.x];

	// Скопировать пустую клетку на позицию нужной фишки
	field[neighborPos.y][neighborPos.x] = '#';

	// Вернуть положительный результат
	return true;
}

vector<Position> GameFieldData::getPos(const char& value) const
{
	Size fieldSize = getSize(); // Размеры поля
	vector<Position> positions; // ...Считать, что результирующий вектор пустой

	for (int i = 0; i < fieldSize.height; i++) // Для каждой строки расстановки
		for (int j = 0; j < fieldSize.length; j++) // Для каждой клетки текущей строки
			// Добавить позицию текущей клетки в результирующий вектор, если ее значение совпадает с заданным
			if (field[i][j] == value) positions.push_back({ j, i });

	// Вернуть результирующий вектор
	return positions;
}

int GameFieldData::countInversions() const
{
	int inversionsCount = 0; // ...Считать, что количество инверсий равно нулю
	vector<char> symbols; // Вектор символов поля
	for (const auto& row : this->field) symbols.insert(symbols.end(), row.begin(), row.end());

	for (int i = 0; i < symbols.size(); i++) // Для каждого символа расстановки
		for (int j = i + 1; j < symbols.size(); j++) // Для каждого символа расстановки после текущего
			// Инкрементировать количество инверсий, если текущий символ больше последующего за текущим
			if (symbols[i] != '#' && symbols[j] != '#' && symbols[i] > symbols[j]) inversionsCount++;

	// Вернуть количество инверсий
	return inversionsCount;
}
