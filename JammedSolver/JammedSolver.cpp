/*!
* \file
* \brief Данный файл содержит в себе реализацию глобальных функций
*/

#include "JammedSolver.h"
#include "PriorityQueue.h"
#include "Node.h"

vector<vector<string>> parseText(const vector<string>& text, const string& separator)
{
	return {};
}

vector<GameFieldData> solveJammed(const GameFieldData& startField, const GameFieldData& goalField)
{
	// Вернуть отсутствие решения, если #у игры нет решения#
	if (!GameFieldData::isSolvable(startField, goalField)) return {};

	// ...Считать, что список открытых узлов с расстановками содержит начальную расстановку
	PriorityQueue<Node<GameFieldData>> openNodes; // Список открытых узлов
	Node<GameFieldData>* root = new Node<GameFieldData>(startField); // Корень дерева - начальная расстановка
	openNodes.enqueue(root, 0);

	// ...Считать, что список закрытых узлов с расстановками пустой
	PriorityQueue<Node<GameFieldData>> closedNodes; // Список закрытых узлов

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

		// Удалить созданные расстановки, которые есть в списке открытых или закрытых узлов
		for (const GameFieldData& currentNewField : newFields) {
			// Получить список открытых и закрытых узлов
			vector<Node<GameFieldData>*> nodesVector = openNodes.getItems();
			vector<Node<GameFieldData>*> tempClosedNodes = closedNodes.getItems();
			nodesVector.insert(nodesVector.cend(), tempClosedNodes.cbegin(), tempClosedNodes.cend());
			
			// Найти в общем списке текущую расстановку
			bool isCurrentFieldExist = false; // Флаг нахождения расстановки
			for (const Node<GameFieldData>* currentListNode : nodesVector)
				isCurrentFieldExist += currentNewField.getField() == currentListNode->getData().getField();

			// Удалить расстановку, если она найдена в списках узлов
			if (isCurrentFieldExist) {
				// Найти текущую расстановку в новых созданных
				auto it = std::find(newFields.begin(), newFields.end(), currentNewField);

				// Удалить расстановку
				if (it != newFields.end()) newFields.erase(it);
			}
		}

		// Вычислить приоритет для созданных расстановок = #манхэттенское расстояние#  + количество ходов от начала
		for (GameFieldData& currentNewField : newFields)
			currentNewField.setManhattanDistance(currentNewField.getManhattanDistance(goalField) + currentNewField.getNumberOfMoves());

		// #Поместить узлы с созданными расстановками в список открытых узлов#
		vector<Node<GameFieldData>*> newNodes; // Новые узлы с новыми расстановками для списка открытых узлов
		for (const GameFieldData& currentNewField : newFields) {
			// Создать новый узел с текущей новой расстановкой
			Node<GameFieldData>* newNode = new Node<GameFieldData>(currentNewField, currentNode);

			// Поместить новый узел с текущей новой расстановкой в вектор новых узлов
			newNodes.push_back(newNode);
		}
		for (Node<GameFieldData>* newNode : newNodes) // Поместить созданные узлы в список открытых узлов
			openNodes.enqueue(newNode, newNode->getData().getManhattanDistance());

		// Попытаться найти среди созданных расстановок целевую
		for (Node<GameFieldData>* newNode : newNodes)
			if (GameFieldData::compareFields(newNode->getData(), goalField))
				findedField = newNode;

		// Переместить текущую расстановку из списка открытых узлов в список закрытых
		closedNodes.enqueue(currentNode, currentNode->getData().getManhattanDistance());
	}

	// #Вычислить путь от начальной расстановки до найденной целевой# и вернуть его
	vector<Node<GameFieldData>*> solution = findedField->getWayFromRoot(findedField);

	// Конвертировать путь для возврата
	vector<GameFieldData> convertedSolution; // Путь для возврата функции
	for (const Node<GameFieldData>* node : solution)
		convertedSolution.push_back(node->getData());

	// Очистить память
	vector<Node<GameFieldData>*> nodesVector = openNodes.getItems(); // Список открытых и закрытых узлов
	vector<Node<GameFieldData>*> tempClosedNodes = closedNodes.getItems();
	nodesVector.insert(nodesVector.cend(), tempClosedNodes.cbegin(), tempClosedNodes.cend());
	for (Node<GameFieldData>* node : nodesVector) delete node;

	// Вернуть решение
	return convertedSolution;
}
