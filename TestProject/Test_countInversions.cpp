#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_countInversions)
	{
	public:
		
		TEST_METHOD(ascendingOrder)
		{
			GameFieldData field({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			Assert::AreEqual(0, field.countInversions());
		}

		TEST_METHOD(descendingOrder)
		{
			GameFieldData field({
				{'7', '6', '5', '4'},
				{'3', '2', '1', '#'} });

			Assert::AreEqual(21, field.countInversions());
		}

		TEST_METHOD(randomOrder)
		{
			GameFieldData field({
				{'4', '6', '5', '1'},
				{'2', '7', '3', '#'} });

			Assert::AreEqual(11, field.countInversions());
		}

		TEST_METHOD(onlyUppercaseAlphas)
		{
			GameFieldData field({
				{'D', 'F', 'E', 'A'},
				{'B', 'G', 'C', '#'} });

			Assert::AreEqual(11, field.countInversions());
		}

		TEST_METHOD(onlyLowercaseAlphas)
		{
			GameFieldData field({
				{'d', 'f', 'e', 'a'},
				{'b', 'g', 'c', '#'} });

			Assert::AreEqual(11, field.countInversions());
		}

		TEST_METHOD(onlyAnyAlphas)
		{
			GameFieldData field({
				{'D', 'F', 'E', 'a'},
				{'B', 'G', 'c', '#'} });

			Assert::AreEqual(6, field.countInversions());
		}

		TEST_METHOD(alphasAndNumbers)
		{
			GameFieldData field({
				{'4', '6', 'E', 'A'},
				{'2', 'G', '3', '#'} });

			Assert::AreEqual(10, field.countInversions());
		}

		TEST_METHOD(emptyCellAtStart)
		{
			GameFieldData field({
				{'#', '4', '6', '5'},
				{'1', '2', '7', '3'} });

			Assert::AreEqual(11, field.countInversions());
		}

		TEST_METHOD(emptyCellAtMiddle)
		{
			GameFieldData field({
				{'4', '6', '5', '#'},
				{'1', '2', '7', '3'} });

			Assert::AreEqual(11, field.countInversions());
		}

		TEST_METHOD(thereAreEqualChips)
		{
			GameFieldData field({
				{'1', '2', '2', '4'},
				{'5', '6', '7', '#'} });

			Assert::AreEqual(0, field.countInversions());
		}

		TEST_METHOD(allChipsAreEqualNumbers)
		{
			GameFieldData field({
				{'0', '0', '0', '0'},
				{'0', '0', '0', '#'} });

			Assert::AreEqual(0, field.countInversions());
		}

		TEST_METHOD(allChipsAreEqualUppercaseAlphas)
		{
			GameFieldData field({
				{'A', 'A', 'A', 'A'},
				{'A', 'A', 'A', '#'} });

			Assert::AreEqual(0, field.countInversions());
		}

		TEST_METHOD(allChipsAreEqualLowercaseAlphas)
		{
			GameFieldData field({
				{'a', 'a', 'a', 'a'},
				{'a', 'a', 'a', '#'} });

			Assert::AreEqual(0, field.countInversions());
		}

		
	};
}
