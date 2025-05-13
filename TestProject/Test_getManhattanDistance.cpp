#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_getManhattanDistance)
	{
	public:
		
		TEST_METHOD(severalChipsAtWrongPositions)
		{
			GameFieldData startField({
				{'0', '4', '7', '0'},
				{'0', '0', '0', '#'} });
			GameFieldData goalField({
				{'0', '7', '4', '0'},
				{'0', '0', '0', '#'} });

			int expected = 2;
			int actual = startField.getManhattanDistance(goalField);

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(allChipsAtWrongPositions)
		{
			GameFieldData startField({
				{'5', '1', '2', '3'},
				{'6', '7', '#', '4'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			int expected = 7;
			int actual = startField.getManhattanDistance(goalField);

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(severalChipsAtCorrectPositions)
		{
			GameFieldData startField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			int expected = 0;
			int actual = startField.getManhattanDistance(goalField);

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(severalCellsToGoalPositions)
		{
			GameFieldData startField({
				{'4', '0', '0', '7'},
				{'0', '0', '0', '#'} });
			GameFieldData goalField({
				{'7', '0', '0', '4'},
				{'0', '0', '0', '#'} });

			int expected = 6;
			int actual = startField.getManhattanDistance(goalField);

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(thereIsEqualChips)
		{
			GameFieldData startField({
				{'0', '4', '4', '0'},
				{'0', '0', '0', '#'} });
			GameFieldData goalField({
				{'4', '0', '0', '4'},
				{'0', '0', '0', '#'} });

			int expected = 4;
			int actual = startField.getManhattanDistance(goalField);

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(longWayToGoalPositions)
		{
			GameFieldData startField({
				{'4', '0', '0', '0'},
				{'0', '0', '#', '7'} });
			GameFieldData goalField({
				{'7', '0', '0', '0'},
				{'0', '0', '#', '4'} });

			int expected = 8;
			int actual = startField.getManhattanDistance(goalField);

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(emptyCellPositionChange)
		{
			GameFieldData startField({
				{'0', '0', '#', '0'},
				{'0', '0', '0', '0'} });
			GameFieldData goalField({
				{'0', '#', '0', '0'},
				{'0', '0', '0', '0'} });

			int expected = 1;
			int actual = startField.getManhattanDistance(goalField);

			Assert::AreEqual(expected, actual);
		}

		
	};
}
