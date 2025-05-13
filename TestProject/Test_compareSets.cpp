#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_compareSets)
	{
	public:
		
		TEST_METHOD(equalFields)
		{
			GameFieldData firstField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData secondField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			Assert::AreEqual(true, GameFieldData::compareSets(firstField, secondField));
		}

		TEST_METHOD(heightDifferentFields)
		{
			GameFieldData firstField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData secondField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '8'},
				{'9', '0', 'A', '#'}});

			Assert::AreEqual(false, GameFieldData::compareSets(firstField, secondField));
		}

		TEST_METHOD(lengthDifferentFields)
		{
			GameFieldData firstField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData secondField({
				{'1', '2', '3', '4', '5'},
				{'6', '7', '8', '9', '#'} });

			Assert::AreEqual(false, GameFieldData::compareSets(firstField, secondField));
		}

		TEST_METHOD(fullyDifferentFieldsSizes)
		{
			GameFieldData firstField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData secondField({
				{'1', '2', '3', '4', '5'},
				{'6', '7', '8', '9', '0'},
				{'A', 'B', 'C', 'D', '#'}});

			Assert::AreEqual(false, GameFieldData::compareSets(firstField, secondField));
		}

		TEST_METHOD(equalChipsOnDifferentPositions)
		{
			GameFieldData firstField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData secondField({
				{'4', '5', '6', '7'},
				{'3', '2', '1', '#'} });

			Assert::AreEqual(true, GameFieldData::compareSets(firstField, secondField));
		}

		TEST_METHOD(chipsRepeating)
		{
			GameFieldData firstField({
				{'1', '2', '2', '3'},
				{'3', '4', '5', '#'} });
			GameFieldData secondField({
				{'1', '2', '2', '3'},
				{'3', '4', '5', '#'} });

			Assert::AreEqual(true, GameFieldData::compareSets(firstField, secondField));
		}

		
	};
}
