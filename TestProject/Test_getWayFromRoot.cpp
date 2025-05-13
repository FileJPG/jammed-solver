#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"
#include "Node.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_getWayFromRoot)
	{
	public:
		
		TEST_METHOD(nodeIsRoot)
		{
			Node<int> node_1(1);
			
			vector<Node<int>> expectedWay = {1};
			vector<Node<int>*> actualWay = node_1.getWayFromRoot(&node_1);

			Assert::AreEqual(expectedWay.size(), actualWay.size());
			for (int i = 0; i < expectedWay.size(); i++)
				Assert::AreEqual(expectedWay[i].getData(), actualWay[i]->getData());
		}

		TEST_METHOD(nodeOnFirstLevel)
		{
			Node<int> node_1(1);
			Node<int> node_2(2, &node_1);
			Node<int> node_3(3, &node_1);

			vector<Node<int>> expectedWay = { 1, 3 };
			vector<Node<int>*> actualWay = node_3.getWayFromRoot(&node_3);

			Assert::AreEqual(expectedWay.size(), actualWay.size());
			for (int i = 0; i < expectedWay.size(); i++)
				Assert::AreEqual(expectedWay[i].getData(), actualWay[i]->getData());
		}

		TEST_METHOD(nodeOnSecondLevel)
		{
			Node<int> node_1(1);
			Node<int> node_2(2, &node_1);
			Node<int> node_3(3, &node_1);
			Node<int> node_4(4, &node_3);
			Node<int> node_5(5, &node_3);

			vector<Node<int>> expectedWay = { 1, 3, 4 };
			vector<Node<int>*> actualWay = node_4.getWayFromRoot(&node_4);

			Assert::AreEqual(expectedWay.size(), actualWay.size());
			for (int i = 0; i < expectedWay.size(); i++)
				Assert::AreEqual(expectedWay[i].getData(), actualWay[i]->getData());
		}

		TEST_METHOD(nodeOnFourthLevel)
		{
			Node<int> node_1(1);
			Node<int> node_2(2, &node_1);
			Node<int> node_3(3, &node_1);
			Node<int> node_4(4, &node_3);
			Node<int> node_5(5, &node_3);
			Node<int> node_6(6, &node_4);
			Node<int> node_7(7, &node_4);
			Node<int> node_8(8, &node_6);
			Node<int> node_9(9, &node_6);

			vector<Node<int>> expectedWay = { 1, 3, 4, 6, 9 };
			vector<Node<int>*> actualWay = node_9.getWayFromRoot(&node_9);

			Assert::AreEqual(expectedWay.size(), actualWay.size());
			for (int i = 0; i < expectedWay.size(); i++)
				Assert::AreEqual(expectedWay[i].getData(), actualWay[i]->getData());
		}

		TEST_METHOD(oneParentNodes)
		{
			Node<int> node_1(1);
			Node<int> node_2(2, &node_1);
			Node<int> node_3(3, &node_2);

			vector<Node<int>> expectedWay = { 1, 2, 3 };
			vector<Node<int>*> actualWay = node_3.getWayFromRoot(&node_3);

			Assert::AreEqual(expectedWay.size(), actualWay.size());
			for (int i = 0; i < expectedWay.size(); i++)
				Assert::AreEqual(expectedWay[i].getData(), actualWay[i]->getData());
		}

		TEST_METHOD(manyLeavesTree)
		{
			Node<int> node_1(1);
			Node<int> node_2(2, &node_1);
			Node<int> node_3(3, &node_1);
			Node<int> node_4(4, &node_1);
			Node<int> node_5(5, &node_2);
			Node<int> node_6(6, &node_2);
			Node<int> node_7(7, &node_2);
			Node<int> node_8(8, &node_6);
			Node<int> node_9(9, &node_6);
			Node<int> node_10(10, &node_6);

			vector<Node<int>> expectedWay = { 1, 2, 6, 10 };
			vector<Node<int>*> actualWay = node_10.getWayFromRoot(&node_10);

			Assert::AreEqual(expectedWay.size(), actualWay.size());
			for (int i = 0; i < expectedWay.size(); i++)
				Assert::AreEqual(expectedWay[i].getData(), actualWay[i]->getData());
		}

		TEST_METHOD(anyNodeHasLeaves)
		{
			Node<int> node_1(1);
			Node<int> node_2(2, &node_1);
			Node<int> node_3(3, &node_1);
			Node<int> node_4(4, &node_2);
			Node<int> node_5(5, &node_2);
			Node<int> node_6(6, &node_3);
			Node<int> node_7(7, &node_3);

			vector<Node<int>> expectedWay = { 1, 2, 5 };
			vector<Node<int>*> actualWay = node_5.getWayFromRoot(&node_5);

			Assert::AreEqual(expectedWay.size(), actualWay.size());
			for (int i = 0; i < expectedWay.size(); i++)
				Assert::AreEqual(expectedWay[i].getData(), actualWay[i]->getData());
		}

		TEST_METHOD(currentNodeIsParent)
		{
			Node<int> node_1(1);
			Node<int> node_2(2, &node_1);
			Node<int> node_3(3, &node_1);
			Node<int> node_4(4, &node_3);
			Node<int> node_5(5, &node_3);
			Node<int> node_6(6, &node_4);

			vector<Node<int>> expectedWay = { 1, 3, 4 };
			vector<Node<int>*> actualWay = node_4.getWayFromRoot(&node_4);

			Assert::AreEqual(expectedWay.size(), actualWay.size());
			for (int i = 0; i < expectedWay.size(); i++)
				Assert::AreEqual(expectedWay[i].getData(), actualWay[i]->getData());
		}

		
	};
}
