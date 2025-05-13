#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_isSolvable)
	{
	public:
		
		TEST_METHOD(baseTest)
		{
			GameFieldData startField({
				{'1', '#', '2', '3'},
				{'5', '6', '7', '4'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(twoEqualChips)
		{
			GameFieldData startField({
				{'1', '#', '2', '3'},
				{'5', '2', '7', '4'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '2', '7', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(severalEqualChips)
		{
			GameFieldData startField({
				{'1', '#', '2', '3'},
				{'2', '2', '7', '4'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'2', '2', '7', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(severalSetsOfTwoEqualChips)
		{
			GameFieldData startField({
				{'1', '#', '2', '3'},
				{'3', '2', '7', '4'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'3', '2', '7', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(severalSetsOfSeveralEqualChips)
		{
			GameFieldData startField({
				{'7', '#', '2', '3'},
				{'3', '2', '7', '4'} });
			GameFieldData goalField({
				{'7', '2', '3', '4'},
				{'3', '2', '7', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(allChipsAreEqual)
		{
			GameFieldData startField({
				{'0', '#', '0', '0'},
				{'0', '0', '0', '0'} });
			GameFieldData goalField({
				{'0', '0', '0', '0'},
				{'0', '0', '0', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(emptyCellsInSameString)
		{
			GameFieldData startField({
				{'1', '2', '3', '4'},
				{'#', '5', '6', '7'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(differentInversionsCount)
		{
			GameFieldData startField({
				{'1', '2', '3', '4'},
				{'5', '7', '6', '#'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			Assert::AreEqual(false, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(equalFields)
		{
			GameFieldData startField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(oneMoveForSolving)
		{
			GameFieldData startField({
				{'1', '2', '3', '#'},
				{'5', '6', '7', '4'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(manyMovesForSolving)
		{
			GameFieldData startField({
				{'6', '5', '1', '2'},
				{'7', '#', '4', '3'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(differentFieldsSizes)
		{
			GameFieldData startField({
				{'1', '2', '3'},
				{'4', '5', '#'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			Assert::AreEqual(false, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(differentFieldsChipSets)
		{
			GameFieldData startField({
				{'A', 'B', 'C', 'D'},
				{'E', 'F', 'G', '#'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			Assert::AreEqual(false, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(onlyAlphaChips)
		{
			GameFieldData startField({
				{'A', '#', 'B', 'C'},
				{'E', 'F', 'G', 'D'} });
			GameFieldData goalField({
				{'A', 'B', 'C', 'D'},
				{'E', 'F', 'G', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		TEST_METHOD(alphaAndNumberChips)
		{
			GameFieldData startField({
				{'A', '#', '1', '2'},
				{'E', '3', 'G', 'D'} });
			GameFieldData goalField({
				{'A', '1', '2', 'D'},
				{'E', '3', 'G', '#'} });

			Assert::AreEqual(true, GameFieldData::isSolvable(startField, goalField));
		}

		
	};
}
