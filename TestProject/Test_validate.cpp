#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_validate)
	{
	public:
		
		TEST_METHOD(validField)
		{
			Field field = {
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'}
			};

			vector<Error> expectedErrors = {};
			vector<Error> actualErrors = GameFieldData::validate(field);

			Assert::AreEqual(expectedErrors.size(), actualErrors.size());
			for (int i = 0; i < expectedErrors.size(); i++)
				Assert::IsTrue(expectedErrors[i] == actualErrors[i]);
		}

		TEST_METHOD(differentStringSizes)
		{
			Field field = {
				{'1', '2'},
				{'5', '6', '7', '#'}
			};

			vector<Error> expectedErrors = {
				Error(incorrectFieldForm)
			};
			vector<Error> actualErrors = GameFieldData::validate(field);

			Assert::AreEqual(expectedErrors.size(), actualErrors.size());
			for (int i = 0; i < expectedErrors.size(); i++)
				Assert::IsTrue(expectedErrors[i] == actualErrors[i]);
		}

		TEST_METHOD(noEmptyCell)
		{
			Field field = {
				{'1', '2', '3', '4'},
				{'5', '6', '7', '8'}
			};

			vector<Error> expectedErrors = {
				Error(incorrectEmptyCellsCount, "", true, 0)
			};
			vector<Error> actualErrors = GameFieldData::validate(field);

			Assert::AreEqual(expectedErrors.size(), actualErrors.size());
			for (int i = 0; i < expectedErrors.size(); i++)
				Assert::IsTrue(expectedErrors[i] == actualErrors[i]);
		}

		TEST_METHOD(severalEmptyCells)
		{
			Field field = {
				{'1', '#', '3', '4'},
				{'5', '6', '7', '#'}
			};

			vector<Error> expectedErrors = {
				Error(incorrectEmptyCellsCount, "", true, 2)
			};
			vector<Error> actualErrors = GameFieldData::validate(field);

			Assert::AreEqual(expectedErrors.size(), actualErrors.size());
			for (int i = 0; i < expectedErrors.size(); i++)
				Assert::IsTrue(expectedErrors[i] == actualErrors[i]);
		}

		TEST_METHOD(chipsWithAlphasOnly)
		{
			Field field = {
				{'A', 'b', 'c', 'D'},
				{'e', 'F', 'g', '#'}
			};

			vector<Error> expectedErrors = {};
			vector<Error> actualErrors = GameFieldData::validate(field);

			Assert::AreEqual(expectedErrors.size(), actualErrors.size());
			for (int i = 0; i < expectedErrors.size(); i++)
				Assert::IsTrue(expectedErrors[i] == actualErrors[i]);
		}

		TEST_METHOD(chipsWithAlphasAndNumbers)
		{
			Field field = {
				{'1', 'b', '3', 'C'},
				{'d', '5', 'E', '#'}
			};

			vector<Error> expectedErrors = {};
			vector<Error> actualErrors = GameFieldData::validate(field);

			Assert::AreEqual(expectedErrors.size(), actualErrors.size());
			for (int i = 0; i < expectedErrors.size(); i++)
				Assert::IsTrue(expectedErrors[i] == actualErrors[i]);
		}

		TEST_METHOD(incorrectSymbols)
		{
			Field field = {
				{'1', '&', '3', '4'},
				{'@', '6', '%', '#'}
			};

			vector<Error> expectedErrors = {
				Error(incorrectSymbolsInField, "&@%")
			};
			vector<Error> actualErrors = GameFieldData::validate(field);

			Assert::AreEqual(expectedErrors.size(), actualErrors.size());
			for (int i = 0; i < expectedErrors.size(); i++)
				Assert::IsTrue(expectedErrors[i] == actualErrors[i]);
		}

		TEST_METHOD(severalErrors)
		{
			Field field = {
				{'1', '#', '3', '4'},
				{'5', '%', '7', '#'}
			};

			vector<Error> expectedErrors = {
				Error(incorrectEmptyCellsCount, "", true, 2),
				Error(incorrectSymbolsInField, "%")
			};
			vector<Error> actualErrors = GameFieldData::validate(field);

			Assert::AreEqual(expectedErrors.size(), actualErrors.size());
			for (int i = 0; i < expectedErrors.size(); i++)
				Assert::IsTrue(expectedErrors[i] == actualErrors[i]);
		}

		TEST_METHOD(allErrors)
		{
			Field field = {
				{'%', '#', '2'},
				{'5', '&', '7', '#'}
			};

			vector<Error> expectedErrors = {
				Error(incorrectFieldForm),
				Error(incorrectEmptyCellsCount, "", true, 2),
				Error(incorrectSymbolsInField, "%&")
			};
			vector<Error> actualErrors = GameFieldData::validate(field);

			Assert::AreEqual(expectedErrors.size(), actualErrors.size());
			for (int i = 0; i < expectedErrors.size(); i++)
				Assert::IsTrue(expectedErrors[i] == actualErrors[i]);
		}

		
	};
}
