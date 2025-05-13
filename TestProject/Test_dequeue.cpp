#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"
#include "PriorityQueue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_dequeue)
	{
	public:
		
		TEST_METHOD(baseTest)
		{
			PriorityQueue<int> actualQueue;
			vector<int> actualItems = { 15, 28 };
			vector<int> actualPriorities = { 2, 1 };
			for (int i = 0; i < actualItems.size(); i++)
				actualQueue.enqueue(actualItems.data() + i, actualPriorities[i]);

			int expectedElement = 28;
			int* actualElement = actualQueue.dequeue();

			vector<int*> expectedQueue = actualQueue.getItems();
			vector<int> expectedItems = { 15 };
			vector<int> expectedPriorities = { 2 };

			Assert::AreEqual(expectedElement, *actualElement);
			Assert::AreEqual(expectedItems.size(), actualQueue.getItems().size());
			Assert::AreEqual(expectedPriorities.size(), actualQueue.getPriorities().size());
			for (int i = 0; i < expectedItems.size(); i++)
			{
				Assert::AreEqual(expectedItems[i], *actualQueue.getItems()[i]);
				Assert::AreEqual(expectedPriorities[i], actualQueue.getPriorities()[i]);
			}
		}

		TEST_METHOD(noElementsInQueue)
		{
			PriorityQueue<int> actualQueue;
			vector<int> actualItems = {};
			vector<int> actualPriorities = {};
			for (int i = 0; i < actualItems.size(); i++)
				actualQueue.enqueue(actualItems.data() + i, actualPriorities[i]);

			int* expectedElement = nullptr;
			int* actualElement = actualQueue.dequeue();

			vector<int*> expectedQueue = actualQueue.getItems();
			vector<int> expectedItems = {};
			vector<int> expectedPriorities = {};

			Assert::AreEqual(expectedElement, actualElement);
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
			vector<int> actualItems = { 15, 28, 24, 48 };
			vector<int> actualPriorities = { 2, 1, 0, 1 };
			for (int i = 0; i < actualItems.size(); i++)
				actualQueue.enqueue(actualItems.data() + i, actualPriorities[i]);

			int expectedElement = 24;
			int* actualElement = actualQueue.dequeue();

			vector<int*> expectedQueue = actualQueue.getItems();
			vector<int> expectedItems = { 15, 28, 48 };
			vector<int> expectedPriorities = { 2, 1, 1 };

			Assert::AreEqual(expectedElement, *actualElement);
			Assert::AreEqual(expectedItems.size(), actualQueue.getItems().size());
			Assert::AreEqual(expectedPriorities.size(), actualQueue.getPriorities().size());
			for (int i = 0; i < expectedItems.size(); i++)
			{
				Assert::AreEqual(expectedItems[i], *actualQueue.getItems()[i]);
				Assert::AreEqual(expectedPriorities[i], actualQueue.getPriorities()[i]);
			}
		}

		TEST_METHOD(equalElementsWithEqualPriorities)
		{
			PriorityQueue<int> actualQueue;
			vector<int> actualItems = { 15, 15 };
			vector<int> actualPriorities = { 2, 2 };
			for (int i = 0; i < actualItems.size(); i++)
				actualQueue.enqueue(actualItems.data() + i, actualPriorities[i]);

			int expectedElement = 15;
			int* actualElement = actualQueue.dequeue();

			vector<int*> expectedQueue = actualQueue.getItems();
			vector<int> expectedItems = { 15 };
			vector<int> expectedPriorities = { 2 };

			Assert::AreEqual(expectedElement, *actualElement);
			Assert::AreEqual(expectedItems.size(), actualQueue.getItems().size());
			Assert::AreEqual(expectedPriorities.size(), actualQueue.getPriorities().size());
			for (int i = 0; i < expectedItems.size(); i++)
			{
				Assert::AreEqual(expectedItems[i], *actualQueue.getItems()[i]);
				Assert::AreEqual(expectedPriorities[i], actualQueue.getPriorities()[i]);
			}
		}

		TEST_METHOD(differentElementsWithEqualPriorities)
		{
			PriorityQueue<int> actualQueue;
			vector<int> actualItems = { 15, 28 };
			vector<int> actualPriorities = { 2, 2 };
			for (int i = 0; i < actualItems.size(); i++)
				actualQueue.enqueue(actualItems.data() + i, actualPriorities[i]);

			int expectedElement = 15;
			int* actualElement = actualQueue.dequeue();

			vector<int*> expectedQueue = actualQueue.getItems();
			vector<int> expectedItems = { 28 };
			vector<int> expectedPriorities = { 2 };

			Assert::AreEqual(expectedElement, *actualElement);
			Assert::AreEqual(expectedItems.size(), actualQueue.getItems().size());
			Assert::AreEqual(expectedPriorities.size(), actualQueue.getPriorities().size());
			for (int i = 0; i < expectedItems.size(); i++)
			{
				Assert::AreEqual(expectedItems[i], *actualQueue.getItems()[i]);
				Assert::AreEqual(expectedPriorities[i], actualQueue.getPriorities()[i]);
			}
		}

		TEST_METHOD(equalElementsWithDifferentlPriorities)
		{
			PriorityQueue<int> actualQueue;
			vector<int> actualItems = { 15, 15 };
			vector<int> actualPriorities = { 2, 1 };
			for (int i = 0; i < actualItems.size(); i++)
				actualQueue.enqueue(actualItems.data() + i, actualPriorities[i]);

			int expectedElement = 15;
			int* actualElement = actualQueue.dequeue();

			vector<int*> expectedQueue = actualQueue.getItems();
			vector<int> expectedItems = { 15 };
			vector<int> expectedPriorities = { 2 };

			Assert::AreEqual(expectedElement, *actualElement);
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
