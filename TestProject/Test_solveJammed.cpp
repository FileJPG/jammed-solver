#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_solveJammed)
	{
	public:
		
		TEST_METHOD(equalFields)
		{
			GameFieldData startField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'}});
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'}});

			vector<GameFieldData> expectedSolution = {
				GameFieldData({
					{'1', '2', '3', '4'},
					{'5', '6', '7', '#'}})
			};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

		TEST_METHOD(oneMoveForSolve)
		{
			GameFieldData startField({
				{'1', '2', '3', '#'},
				{'5', '6', '7', '4'}});
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'}});

			vector<GameFieldData> expectedSolution = {
				GameFieldData({
					{'1', '2', '3', '#'},
					{'5', '6', '7', '4'}}),
				GameFieldData({
					{'1', '2', '3', '4'},
					{'5', '6', '7', '#'}})
			};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

		TEST_METHOD(severalMovesForSolve)
		{
			GameFieldData startField({
				{'1', '#', '2', '3'},
				{'5', '6', '7', '4'}});
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'}});

			vector<GameFieldData> expectedSolution = {
				GameFieldData({
					{'1', '#', '2', '3'},
					{'5', '6', '7', '4'}}),
				GameFieldData({
					{'1', '2', '#', '3'},
					{'5', '6', '7', '4'}}),
				GameFieldData({
					{'1', '2', '3', '#'},
					{'5', '6', '7', '4'}}),
				GameFieldData({
					{'1', '2', '3', '4'},
					{'5', '6', '7', '#'}})
			};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

		TEST_METHOD(manyMovesForSolve)
		{
			GameFieldData startField({
				{'1', '6', '2', '3'},
				{'#', '5', '7', '4'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			vector<GameFieldData> expectedSolution = {
				GameFieldData({
					{'1', '6', '2', '3'},
					{'#', '5', '7', '4'}}),
				GameFieldData({
					{'1', '6', '2', '3'},
					{'5', '#', '7', '4'}}),
				GameFieldData({
					{'1', '#', '2', '3'},
					{'5', '6', '7', '4'}}),
				GameFieldData({
					{'1', '2', '#', '3'},
					{'5', '6', '7', '4'}}),
				GameFieldData({
					{'1', '2', '3', '#'},
					{'5', '6', '7', '4'}}),
				GameFieldData({
					{'1', '2', '3', '4'},
					{'5', '6', '7', '#'}})
			};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

		TEST_METHOD(thereIsSetOfSameChips)
		{
			GameFieldData startField({
				{'1', '#', '2', '2'},
				{'5', '6', '7', '4'} });
			GameFieldData goalField({
				{'1', '2', '2', '4'},
				{'5', '6', '7', '#'} });

			vector<GameFieldData> expectedSolution = {
				GameFieldData({
					{'1', '#', '2', '2'},
					{'5', '6', '7', '4'}}),
				GameFieldData({
					{'1', '2', '#', '2'},
					{'5', '6', '7', '4'}}),
				GameFieldData({
					{'1', '2', '2', '#'},
					{'5', '6', '7', '4'}}),
				GameFieldData({
					{'1', '2', '2', '4'},
					{'5', '6', '7', '#'}})
			};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

		TEST_METHOD(thereIsSeveralSetsOfSameChips)
		{
			GameFieldData startField({
				{'1', '#', '2', '2'},
				{'5', '6', '7', '7'} });
			GameFieldData goalField({
				{'1', '2', '2', '7'},
				{'5', '6', '7', '#'} });

			vector<GameFieldData> expectedSolution = {
				GameFieldData({
					{'1', '#', '2', '2'},
					{'5', '6', '7', '7'}}),
				GameFieldData({
					{'1', '2', '#', '2'},
					{'5', '6', '7', '7'}}),
				GameFieldData({
					{'1', '2', '2', '#'},
					{'5', '6', '7', '7'}}),
				GameFieldData({
					{'1', '2', '2', '7'},
					{'5', '6', '7', '#'}})
			};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

		TEST_METHOD(onlyEqualChips)
		{
			GameFieldData startField({
				{'#', '0', '0', '0'},
				{'0', '0', '0', '0'} });
			GameFieldData goalField({
				{'0', '0', '0', '#'},
				{'0', '0', '0', '0'} });

			vector<GameFieldData> expectedSolution = {
				GameFieldData({
					{'#', '0', '0', '0'},
					{'0', '0', '0', '0'} }),
				GameFieldData({
					{'0', '#', '0', '0'},
					{'0', '0', '0', '0'} }),
				GameFieldData({
					{'0', '0', '#', '0'},
					{'0', '0', '0', '0'} }),
				GameFieldData({
					{'0', '0', '0', '#'},
					{'0', '0', '0', '0'} }),
			};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

		TEST_METHOD(differentFieldsParities)
		{
			GameFieldData startField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData goalField({
				{'1', '2', '3', '4'},
				{'5', '7', '6', '#'} });

			vector<GameFieldData> expectedSolution = {};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

		TEST_METHOD(differentFieldsChipSets)
		{
			GameFieldData startField({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData goalField({
				{'A', 'B', 'C', 'D'},
				{'E', 'F', 'G', '#'} });

			vector<GameFieldData> expectedSolution = {};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

		TEST_METHOD(onlyAlphas)
		{
			GameFieldData startField({
				{'A', '#', 'B', 'C'},
				{'E', 'F', 'G', 'D'} });
			GameFieldData goalField({
				{'A', 'B', 'C', 'D'},
				{'E', 'F', 'G', '#'} });

			vector<GameFieldData> expectedSolution = {
				GameFieldData({
					{'A', '#', 'B', 'C'},
					{'E', 'F', 'G', 'D'} }),
				GameFieldData({
					{'A', 'B', '#', 'C'},
					{'E', 'F', 'G', 'D'} }),
				GameFieldData({
					{'A', 'B', 'C', '#'},
					{'E', 'F', 'G', 'D'} }),
				GameFieldData({
					{'A', 'B', 'C', 'D'},
					{'E', 'F', 'G', '#'} }),
			};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

		TEST_METHOD(alphasAndNumbers)
		{
			GameFieldData startField({
				{'A', '#', '1', '2'},
				{'E', '3', 'G', 'D'} });
			GameFieldData goalField({
				{'A', '1', '2', 'D'},
				{'E', '3', 'G', '#'} });

			vector<GameFieldData> expectedSolution = {
				GameFieldData({
					{'A', '#', '1', '2'},
					{'E', '3', 'G', 'D'} }),
				GameFieldData({
					{'A', '1', '#', '2'},
					{'E', '3', 'G', 'D'} }),
				GameFieldData({
					{'A', '1', '2', '#'},
					{'E', '3', 'G', 'D'} }),
				GameFieldData({
					{'A', '1', '2', 'D'},
					{'E', '3', 'G', '#'} }),
			};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

		TEST_METHOD(complexTest)
		{
			GameFieldData startField({
				{'A', '1', '2', 'a'},
				{'2', 'B', 'B', '#'} });
			GameFieldData goalField({
				{'A', 'B', '1', '2'},
				{'2', 'B', 'a', '#'} });

			vector<GameFieldData> expectedSolution = {
				GameFieldData({
					{'A', '1', '2', 'a'},
					{'2', 'B', 'B', '#'} }),
				GameFieldData({
					{'A', '1', '2', '#'},
					{'2', 'B', 'B', 'a'} }),
				GameFieldData({
					{'A', '1', '#', '2'},
					{'2', 'B', 'B', 'a'} }),
				GameFieldData({
					{'A', '#', '1', '2'},
					{'2', 'B', 'B', 'a'} }),
				GameFieldData({
					{'A', 'B', '1', '2'},
					{'2', '#', 'B', 'a'} }),
				GameFieldData({
					{'A', 'B', '1', '2'},
					{'2', 'B', '#', 'a'} }),
				GameFieldData({
					{'A', 'B', '1', '2'},
					{'2', 'B', 'a', '#'} })
			};
			vector<GameFieldData> actualSolution = solveJammed(startField, goalField);

			Assert::AreEqual(expectedSolution.size(), actualSolution.size());
			for (int i = 0; i < expectedSolution.size(); i++)
				Assert::IsTrue(expectedSolution[i].getField() == actualSolution[i].getField());
		}

	};
}
