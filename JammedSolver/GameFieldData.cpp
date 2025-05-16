/*!
* \file
* \brief Данный файл содержит в себе реализацию функций класса GameFieldData
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
	vector<Error> errors; // Найденные ошибки

	// Проверить расстановку на прямоугольную форму...
	// Вернуть ошибку, если расстановка пустая
	if (field.empty()) {
		errors.push_back(Error(incorrectFieldForm));
		return errors;
	}

	for (const auto& row : field) // Для каждой строки расстановки
	{
		// Добавить ошибку, если длина текущей строки расстановки отличается от длины первой строки
		if (row.size() != field[0].size()) {
			errors.push_back(Error(incorrectFieldForm));
			break;
		}
	}

	// Проверить клетки расстановки...
	int emptyCellCount = 0; // ...Считать, что счетчик пустой клетки равен нулю

	vector<char> fieldSymbols; // ...Получить набор символов расстановки
	for (const auto& row : field)
		fieldSymbols.insert(fieldSymbols.end(), row.begin(), row.end());

	Error errorIncorrectSymbols(incorrectSymbolsInField);
	for (const auto& fieldSymbol : fieldSymbols) // Для каждой клетки расстановки
	{
		// Инкрементировать счетчик пустой клетки, если текущая клетка является пустой
		if (fieldSymbol == '#')
			emptyCellCount++;

		// Добавить символ в ошибку, если текущий символ не является допустимым для клетки
		if (!isalnum(fieldSymbol) && fieldSymbol != '#')
			errorIncorrectSymbols.str.push_back(fieldSymbol);
	}

	// Добавить ошибку, если в расстановке не одна пустая клетка
	if (emptyCellCount != 1)
		errors.push_back(Error(incorrectEmptyCellsCount, "", true, emptyCellCount));

	// Добавить ошибку, если есть хотя бы один недопустимый символ
	if (!errorIncorrectSymbols.str.empty())
		errors.push_back(errorIncorrectSymbols);

	// Вернуть найденные ошибки
	return errors;
}

bool GameFieldData::isSolvable(const GameFieldData& startField, const GameFieldData& goalField)
{
	// Считать, что игра нерешаема, если #наборы фишек полей разные#
	if (!GameFieldData::compareSets(startField, goalField)) 
		return false;

	// Считать, что игра решаема, если в наборе фишек полей есть хотя бы две одинаковые фишки
	unordered_set<char> fieldSymbols; // Множество символов расстановки
	for (const auto& row : startField.field)
		fieldSymbols.insert(row.cbegin(), row.cend());

	if (fieldSymbols.size() < startField.getSize().square())
		return true;

	// #Посчитать количество инверсий для начальной и целевой расстановок#
	int firstInversionsCount = startField.countInversions();
	int secondInversionsCount = goalField.countInversions();

	// #Вычислить позиции пустой клетки для начальной и целевой расстановок#
	Position firstEmptyCellPos = startField.getPos('#')[0];
	Position secondEmptyCellPos = goalField.getPos('#')[0];

	// Считать, что игра решаема, если четность суммы инверсии и номера строки с пустой клеткой на первом поле совпадает с четностью на втором
	return (firstInversionsCount + firstEmptyCellPos.y) % 2 == (secondInversionsCount + secondEmptyCellPos.y) % 2;
}

bool GameFieldData::compareFields(const GameFieldData& firstField, const GameFieldData& secondField)
{
	Size firstFieldSize = firstField.getSize(); // Размеры первой расстановки
	Size secondFieldSize = secondField.getSize(); // Размеры второй расстановки

	// Вернуть отрицательный результат, если #размеры расстановок разные#
	if (firstFieldSize != secondFieldSize)
		return false;

	// Сравнить клетки расстановок...
	for (int i = 0; i < firstFieldSize.height; i++) // Для каждой позиции расстановки
		for (int j = 0; j < firstFieldSize.length; j++)
			if (firstField.field[i][j] != secondField.field[i][j])
				return false; // Вернуть отрицательный результат, если клетки расстановок на текущей позиции не совпадают

	// Вернуть положительный результат
	return true;
}

bool GameFieldData::compareSets(const GameFieldData& firstField, const GameFieldData& secondField)
{
	// Вернуть отрицательный результат, если #размеры расстановок разные#
	if (firstField.getSize() != secondField.getSize())
		return false;

	// Получить наборы символов расстановок...
	std::unordered_multiset<char> firstSymbolsSet, secondSymbolsSet; // Множества символов расстановок

	for (const auto& row : firstField.field) // Для каждой строки расстановки обоих полей
		firstSymbolsSet.insert(row.begin(), row.end()); // Вставить в множества символов расстановок текущие строки расстановок соответственно

	for (const auto& row : secondField.field)
		secondSymbolsSet.insert(row.begin(), row.end());

	// Вернуть результат сравнения множеств символов расстановок
	return firstSymbolsSet == secondSymbolsSet;
}

Field GameFieldData::convert(const vector<string>& rawField)
{
	Field field; // Расстановка в новом формате

	for (const auto& rawRow : rawField)
	{
		vector<char> row; // Строка расстановки в новом формате

		// Добавить символы текущей строки
		for (const auto& symbol : rawRow)
			row.push_back(symbol);

		// Добавить текущую строку в новом формате
		field.push_back(row);
	}

	return field;
}

vector<GameFieldData> GameFieldData::getMoves() const
{
	Position emptyCellPos = getPos('#')[0]; // ...#Вычислить позицию пустой клетки в расстановке#

	vector<GameFieldData> moves; // ...Считать, что результирующий вектор с новыми расстановками пустой

	vector<Direction> directions = {up, down, right, left}; // Направления для ходов

	for (const Direction& direction : directions) // Для каждой соседней фишки пустой клетки
	{
		// Создать текущую расстановку и в ней #переставить текущую фишку на пустую клетку#
		GameFieldData currentMove(field, numberOfMoves + 1); // Текущий ход

		bool isCurrentMoveValid = currentMove.swap(direction);

		// Положить новую расстановку в результирующий вектор, если текущий ход валидный
		if (isCurrentMoveValid) 
			moves.push_back(currentMove);
	}

	// Вернуть вектор с созданными расстановками
	return moves;
}

int GameFieldData::getManhattanDistance(const GameFieldData& goalField) const
{
	int fieldSizeX = getSize().length; // Длина поля
	int fieldSizeY = getSize().height; // Высота поля

	int totalDistance = 0; // ...Считать, что манхэттенское расстояние не найдено

	vector<vector<bool>> occupied(fieldSizeY, vector<bool>(fieldSizeX, false)); // ...Считать, что ни одна фишка текущей расстановки не привязана к позиции в целевой расстановке

	for (int y1 = 0; y1 < fieldSizeY; y1++) { // Для каждой фишки текущей расстановки
		for (int x1 = 0; x1 < fieldSizeX; x1++) {
			if (field[y1][x1] == '#') continue;

			Position bestPos; // Самая выгодная целевая позиция для текущей фишки
			int minDistance = INT_MAX; // Манхэттенское расстояние до самой выгодной целевой позиции

			// Найти ближайшую незанятую целевую позицию для текущей фишки...
			for (int y2 = 0; y2 < fieldSizeY; y2++) { // Для каждой незанятой целевой позиции расстановки для текущей фишки
				for (int x2 = 0; x2 < fieldSizeX; x2++) {
					if (!occupied[y2][x2] && field[y1][x1] == goalField.field[y2][x2])
					{
						// Посчитать манхэттенское расстояние от рассматриваемой фишки до текущей позиции
						int currentDistance = abs(y1 - y2) + abs(x1 - x2);

						// Для рассматриваемой фишки привязать текущую позицию, если расстояние от фишки до текущей позиции минимальное
						if (currentDistance < minDistance)
						{
							// Изменить минимальное расстояние
							minDistance = currentDistance;

							// Изменить самую выгодную целевую позицию фишки
							bestPos = {x2, y2};
						}
					}
				}
			}
			// Посчитать манхэттенское расстояние от текущей фишки до найденной целевой позиции и прибавить его к результату
			totalDistance += minDistance;

			// Привязать позицию к фишке
			occupied[bestPos.y][bestPos.x] = true;
		}
	}
	// Вернуть сумму манхэттенских расстояний от всех фишек текущей расстановки до их целевых позиций
	return totalDistance;
}

bool GameFieldData::swap(const Direction& direction)
{
	// #Получить позицию пустой клетки#
	Position emptyCellPos = getPos('#')[0];

	// Получить позицию нужной фишки, исходя из заданного направления
	Position neighborPos = emptyCellPos; // Позиция соседней фишки
	switch (direction) {
		case up:	neighborPos.y--; break;
		case down:	neighborPos.y++; break;
		case right: neighborPos.x++; break;
		case left:	neighborPos.x--; break;
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

	for (int y = 0; y < fieldSize.height; y++) // Для каждой строки расстановки
		for (int x = 0; x < fieldSize.length; x++) // Для каждой клетки текущей строки
			if (field[y][x] == value) 
				positions.push_back({ x, y }); // Добавить позицию текущей клетки в результирующий вектор, если ее значение совпадает с заданным

	// Вернуть результирующий вектор
	return positions;
}

int GameFieldData::countInversions() const
{
	int inversionsCount = 0; // ...Считать, что количество инверсий равно нулю

	vector<char> fieldSymbols; // Вектор символов поля
	for (const auto& row : this->field) 
		fieldSymbols.insert(fieldSymbols.end(), row.begin(), row.end());

	for (int i = 0; i < fieldSymbols.size(); i++) // Для каждого символа расстановки
		for (int j = i + 1; j < fieldSymbols.size(); j++) // Для каждого символа расстановки после текущего
			if (fieldSymbols[i] != '#' && fieldSymbols[j] != '#' && fieldSymbols[i] > fieldSymbols[j]) 
				inversionsCount++; // Инкрементировать количество инверсий, если текущий символ больше последующего за текущим

	// Вернуть количество инверсий
	return inversionsCount;
}
