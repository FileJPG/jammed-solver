/*!
* \file
* \brief Данный файл содержит в себе реализацию глобальных функций
*/

#include <fstream>
#include "JammedSolver.h"
#include "PriorityQueue.h"
#include "Node.h"

bool readFile(const string& filePath, vector<string>& data)
{
	// Очистить входные данные
	data.clear();

	// Попытаться открыть файл и вернуть ошибку, если файл не открывается
	std::ifstream inputFile(filePath);
	if (!inputFile.is_open())
		return false;

	string currentLine;
	while (std::getline(inputFile, currentLine)) // Пока не конец файла прочитать текущую строку
		data.push_back(currentLine);

	// Закрыть файл
	inputFile.close();
	
	return true;
}

vector<vector<string>> parseText(const vector<string>& text, const string& separator)
{
	vector<vector<string>> textBlocks; // Блоки текста
	vector<string> currentBlock; // Текущий блок текста

	for (int i = 0; i < text.size(); i++) { // Для каждой строки текста
		if (text[i] == separator) { // Если текущая строка является заданным разделителем
			if (!currentBlock.empty()) // Если текущий блок текста не пустой
			{
				// Выгрузить текущий блок текста в блоки
				textBlocks.push_back(currentBlock);

				// Перейти к следующему блоку текста
				currentBlock.clear();
			}
		}
		else
		{
			// Добавить текущую строку в конец текущего блока текста
			currentBlock.push_back(text[i]);
		}
	}

	// Выгрузить последний блок текста в блоки
	if (!currentBlock.empty())
		textBlocks.push_back(currentBlock);

	return textBlocks;
}

vector<GameFieldData> solveJammed(const GameFieldData& startField, const GameFieldData& goalField)
{
	// Вернуть отсутствие решения, если #у игры нет решения#
	if (!GameFieldData::isSolvable(startField, goalField)) 
		return {};

	// ...Считать, что список открытых узлов с расстановками содержит начальную расстановку
	PriorityQueue<Node<GameFieldData>> openNodes; // Список открытых узлов
	Node<GameFieldData>* root = new Node<GameFieldData>(startField); // Корень дерева - начальная расстановка
	openNodes.enqueue(root, 0);

	// ...Считать, что список закрытых узлов с расстановками пустой
	vector<Node<GameFieldData>*> closedNodes; // Список закрытых узлов

	// ...Считать, что целевая расстановка найдена, если #она совпадает с начальной#
	Node<GameFieldData>* findedField = nullptr; // Найденная целевая расстановка
	if (GameFieldData::compareFields(startField, goalField))
		findedField = root;

	while (!findedField && !openNodes.isEmpty()) // Пока целевая расстановка не найдена и список открытых узлов не пустой
	{
		// #Выбрать из списка открытых узлов с расстановками расстановку с наибольшим приоритетом#
		Node<GameFieldData>* currentNode = openNodes.dequeue();

		// #Создать все возможные ходы для текущей расстановки#
		vector<GameFieldData> newFields = currentNode->getData().getMoves();

		// Удалить созданные расстановки, которые уже есть в списке открытых или закрытых узлов
		for (const GameFieldData& currentNewField : newFields) 
		{
			// Получить общий список открытых и закрытых узлов
			vector<Node<GameFieldData>*> allNodesList = openNodes.getItems();
			allNodesList.insert(allNodesList.cend(), closedNodes.cbegin(), closedNodes.cend());
			
			// Найти в списках открытых и закрытых узлов текущую расстановку
			vector<Node<GameFieldData>*> openNodesVector = openNodes.getItems(); // Список открытых узлов в виде вектора
			bool isCurrentNewFieldExist = false; // Флаг нахождения текущей расстановки в списках

			for (const Node<GameFieldData>* currentNode : allNodesList)
				if (currentNewField.field == currentNode->getData().field) {
					isCurrentNewFieldExist = true;
					break;
				}

			// Удалить расстановку, если она найдена в общем списке узлов
			if (isCurrentNewFieldExist) {
				// Найти текущую расстановку в новых созданных
				auto it = std::find(newFields.begin(), newFields.end(), currentNewField);

				// Удалить расстановку
				if (it != newFields.end()) newFields.erase(it);
			}
		}

		// Вычислить приоритет для созданных расстановок = #манхэттенское расстояние#  + количество ходов от начала
		for (GameFieldData& currentNewField : newFields)
			currentNewField.setManhattanDistance(currentNewField.getManhattanDistance(goalField) + currentNewField.numberOfMoves);

		// #Поместить узлы с созданными расстановками в список открытых узлов#, попробовав найти среди них целевую
		for (const GameFieldData& currentNewField : newFields) // Для каждой новой расстановки
		{
			// Создать новый узел с текущей новой расстановкой
			Node<GameFieldData>* newNode = new Node<GameFieldData>(currentNewField, currentNode);

			// Поместить новый узел в список открытых узлов
			openNodes.enqueue(newNode, newNode->getData().manhattanDistance);

			// Проверить, не является ли текущая расстановка целевой
			if (GameFieldData::compareFields(currentNewField, goalField))
				findedField = newNode;
		}

		// Переместить текущую расстановку из списка открытых узлов в список закрытых
		closedNodes.push_back(currentNode);
	}

	// #Вычислить путь от начальной расстановки до найденной целевой# и вернуть его
	vector<Node<GameFieldData>*> solution = findedField->getWayFromRoot(findedField);

	// Конвертировать путь для возврата
	vector<GameFieldData> convertedSolution; // Путь для возврата функции
	for (const Node<GameFieldData>* node : solution)
		convertedSolution.push_back(node->getData());

	// Очистить память
	vector<Node<GameFieldData>*> openNodesVector = openNodes.getItems(); // Список открытых и закрытых узлов
	for (Node<GameFieldData>* node : openNodesVector) delete node;
	for (Node<GameFieldData>* node : closedNodes) delete node;

	// Вернуть решение
	return convertedSolution;
}
