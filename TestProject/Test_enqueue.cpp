#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"
#include "PriorityQueue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_enqueue)
	{
	public:
		
		TEST_METHOD(baseTest)
		{
			PriorityQueue<int> actualQueue;
			vector<int> actualItems = { 15, 28 };
			vector<int> actualPriorities = { 2, 1 };
			for (int i = 0; i < actualItems.size(); i++)
				actualQueue.enqueue(actualItems.data() + i, actualPriorities[i]);

			int newItem = 11;
			int newPriority = 3;

			actualQueue.enqueue(&newItem, newPriority);

			vector<int> expectedItems = {15, 28, 11};
			vector<int> expectedPriorities = { 2, 1, 3 };

			Assert::AreEqual(expectedItems.size(), actualQueue.getItems().size());
			Assert::AreEqual(expectedPriorities.size(), actualQueue.getPriorities().size());
			for (int i = 0; i < expectedItems.size(); i++)
			{
				Assert::AreEqual(expectedItems[i], *actualQueue.getItems()[i]);
				Assert::AreEqual(expectedPriorities[i], actualQueue.getPriorities()[i]);
			}
		}

		TEST_METHOD(newElementAlreadyExistsInQueue)
		{
			PriorityQueue<int> actualQueue;
			vector<int> actualItems = { 15, 28 };
			vector<int> actualPriorities = { 2, 1 };
			for (int i = 0; i < actualItems.size(); i++)
				actualQueue.enqueue(actualItems.data() + i, actualPriorities[i]);

			int newItem = 28;
			int newPriority = 1;

			actualQueue.enqueue(&newItem, newPriority);

			vector<int> expectedItems = { 15, 28, 28 };
			vector<int> expectedPriorities = { 2, 1, 1 };

			Assert::AreEqual(expectedItems.size(), actualQueue.getItems().size());
			Assert::AreEqual(expectedPriorities.size(), actualQueue.getPriorities().size());
			for (int i = 0; i < expectedItems.size(); i++)
			{
				Assert::AreEqual(expectedItems[i], *actualQueue.getItems()[i]);
				Assert::AreEqual(expectedPriorities[i], actualQueue.getPriorities()[i]);
			}
		}

		TEST_METHOD(emptyQueue)
		{
			PriorityQueue<int> actualQueue;
			vector<int> actualItems = {};
			vector<int> actualPriorities = {};
			for (int i = 0; i < actualItems.size(); i++)
				actualQueue.enqueue(actualItems.data() + i, actualPriorities[i]);

			int newItem = 11;
			int newPriority = 3;

			actualQueue.enqueue(&newItem, newPriority);

			vector<int> expectedItems = { 11 };
			vector<int> expectedPriorities = { 3 };

			Assert::AreEqual(expectedItems.size(), actualQueue.getItems().size());
			Assert::AreEqual(expectedPriorities.size(), actualQueue.getPriorities().size());
			for (int i = 0; i < expectedItems.size(); i++)
			{
				Assert::AreEqual(expectedItems[i], *actualQueue.getItems()[i]);
				Assert::AreEqual(expectedPriorities[i], actualQueue.getPriorities()[i]);
			}
		}

		TEST_METHOD(oneElementInQueue)
		{
			PriorityQueue<int> actualQueue;
			vector<int> actualItems = { 15 };
			vector<int> actualPriorities = { 2 };
			for (int i = 0; i < actualItems.size(); i++)
				actualQueue.enqueue(actualItems.data() + i, actualPriorities[i]);

			int newItem = 11;
			int newPriority = 3;

			actualQueue.enqueue(&newItem, newPriority);

			vector<int> expectedItems = { 15, 11 };
			vector<int> expectedPriorities = { 2, 3 };

			Assert::AreEqual(expectedItems.size(), actualQueue.getItems().size());
			Assert::AreEqual(expectedPriorities.size(), actualQueue.getPriorities().size());
			for (int i = 0; i < expectedItems.size(); i++)
			{
				Assert::AreEqual(expectedItems[i], *actualQueue.getItems()[i]);
				Assert::AreEqual(expectedPriorities[i], actualQueue.getPriorities()[i]);
			}
		}

		TEST_METHOD(manyElementsInQueue)
		{
			PriorityQueue<int> actualQueue;
			vector<int> actualItems = { 15, 28, 34, 10, 2 };
			vector<int> actualPriorities = { 2, 1, 3, 1, 4 };
			for (int i = 0; i < actualItems.size(); i++)
				actualQueue.enqueue(actualItems.data() + i, actualPriorities[i]);

			int newItem = 11;
			int newPriority = 3;

			actualQueue.enqueue(&newItem, newPriority);

			vector<int> expectedItems = { 15, 28, 34, 10, 2, 11 };
			vector<int> expectedPriorities = { 2, 1, 3, 1, 4, 3 };

			Assert::AreEqual(expectedItems.size(), actualQueue.getItems().size());
			Assert::AreEqual(expectedPriorities.size(), actualQueue.getPriorities().size());
			for (int i = 0; i < expectedItems.size(); i++)
			{
				Assert::AreEqual(expectedItems[i], *actualQueue.getItems()[i]);
				Assert::AreEqual(expectedPriorities[i], actualQueue.getPriorities()[i]);
			}
		}

		
	};
}
