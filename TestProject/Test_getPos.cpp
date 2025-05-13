#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_getPos)
	{
	public:
		
		TEST_METHOD(averagePosOfOneEmptyCell)
		{
			GameFieldData field({
				{'1', '2', '3', '4'},
				{'5', '#', '6', '7'} });
			char value = '#';

			vector<Position> expectedPositions = {
				{1, 1}
			};
			vector<Position> actualPositions = field.getPos(value);

			Assert::AreEqual(expectedPositions.size(), actualPositions.size());
			for (int i = 0; i < expectedPositions.size(); i++)
				Assert::IsTrue(expectedPositions[i] == actualPositions[i]);
		}

		TEST_METHOD(averagePosOfOneNumber)
		{
			GameFieldData field({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			char value = '5';

			vector<Position> expectedPositions = {
				{0, 1}
			};
			vector<Position> actualPositions = field.getPos(value);

			Assert::AreEqual(expectedPositions.size(), actualPositions.size());
			for (int i = 0; i < expectedPositions.size(); i++)
				Assert::IsTrue(expectedPositions[i] == actualPositions[i]);
		}

		TEST_METHOD(averagePosOfOneAlpha)
		{
			GameFieldData field({
				{'A', 'B', 'C', 'D'},
				{'E', 'F', 'G', '#'} });
			char value = 'D';

			vector<Position> expectedPositions = {
				{3, 0}
			};
			vector<Position> actualPositions = field.getPos(value);

			Assert::AreEqual(expectedPositions.size(), actualPositions.size());
			for (int i = 0; i < expectedPositions.size(); i++)
				Assert::IsTrue(expectedPositions[i] == actualPositions[i]);
		}

		TEST_METHOD(averagePosOfSeveralNumbers)
		{
			GameFieldData field({
				{'1', '2', '3', '2'},
				{'5', '6', '2', '#'} });
			char value = '2';

			vector<Position> expectedPositions = {
				{1, 0},
				{3, 0},
				{2, 1}
			};
			vector<Position> actualPositions = field.getPos(value);

			Assert::AreEqual(expectedPositions.size(), actualPositions.size());
			for (int i = 0; i < expectedPositions.size(); i++)
				Assert::IsTrue(expectedPositions[i] == actualPositions[i]);
		}

		TEST_METHOD(firstPosOfOneElement)
		{
			GameFieldData field({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			char value = '1';

			vector<Position> expectedPositions = {
				{0, 0}
			};
			vector<Position> actualPositions = field.getPos(value);

			Assert::AreEqual(expectedPositions.size(), actualPositions.size());
			for (int i = 0; i < expectedPositions.size(); i++)
				Assert::IsTrue(expectedPositions[i] == actualPositions[i]);
		}

		TEST_METHOD(lastPosOfOneElement)
		{
			GameFieldData field({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			char value = '#';

			vector<Position> expectedPositions = {
				{3, 1}
			};
			vector<Position> actualPositions = field.getPos(value);

			Assert::AreEqual(expectedPositions.size(), actualPositions.size());
			for (int i = 0; i < expectedPositions.size(); i++)
				Assert::IsTrue(expectedPositions[i] == actualPositions[i]);
		}

		
	};
}
