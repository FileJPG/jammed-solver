#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_getMoves)
	{
	public:

		TEST_METHOD(noMovesAvailable)
		{
			GameFieldData field({
				{'#'} });

			vector<GameFieldData> expectedMoves = {};
			vector<GameFieldData> actualMoves = field.getMoves();

			Assert::AreEqual(expectedMoves.size(), actualMoves.size());
			for (int i = 0; i < expectedMoves.size(); i++)
				Assert::IsTrue(expectedMoves[i] == actualMoves[i]);
		}
		
		TEST_METHOD(oneMoveAvailable)
		{
			GameFieldData field({
				{'1', '#'} });

			vector<GameFieldData> expectedMoves = {
				GameFieldData({
					{'#', '1'}}),
			};
			vector<GameFieldData> actualMoves = field.getMoves();

			Assert::AreEqual(expectedMoves.size(), actualMoves.size());
			for (int i = 0; i < expectedMoves.size(); i++)
				Assert::IsTrue(expectedMoves[i] == actualMoves[i]);
		}

		TEST_METHOD(twoMovesAvailable)
		{
			GameFieldData field({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			vector<GameFieldData> expectedMoves = {
				GameFieldData({
					{'1', '2', '3', '#'},
					{'5', '6', '7', '4'}}),
				GameFieldData({
					{'1', '2', '3', '4'},
					{'5', '6', '#', '7'}}),
			};
			vector<GameFieldData> actualMoves = field.getMoves();

			Assert::AreEqual(expectedMoves.size(), actualMoves.size());
			for (int i = 0; i < expectedMoves.size(); i++)
				Assert::IsTrue(expectedMoves[i] == actualMoves[i]);
		}

		TEST_METHOD(threeMovesAvailable)
		{
			GameFieldData field({
				{'1', '2', '3', '4'},
				{'5', '6', '#', '7'} });

			vector<GameFieldData> expectedMoves = {
				GameFieldData({
					{'1', '2', '#', '4'},
					{'5', '6', '3', '7'}}),
				GameFieldData({
					{'1', '2', '3', '4'},
					{'5', '6', '7', '#'}}),
				GameFieldData({
					{'1', '2', '3', '4'},
					{'5', '#', '6', '7'}}),
			};
			vector<GameFieldData> actualMoves = field.getMoves();

			Assert::AreEqual(expectedMoves.size(), actualMoves.size());
			for (int i = 0; i < expectedMoves.size(); i++)
				Assert::IsTrue(expectedMoves[i] == actualMoves[i]);
		}

		TEST_METHOD(allMovesAvailable)
		{
			GameFieldData field({
				{'1', '2', '3'},
				{'4', '#', '5'},
				{'6', '7', '8'}});

			vector<GameFieldData> expectedMoves = {
				GameFieldData({
					{'1', '#', '3'},
					{'4', '2', '5'},
					{'6', '7', '8'}}),
				GameFieldData({
					{'1', '2', '3'},
					{'4', '7', '5'},
					{'6', '#', '8'}}),
				GameFieldData({
					{'1', '2', '3'},
					{'4', '5', '#'},
					{'6', '7', '8'}}),
				GameFieldData({
					{'1', '2', '3'},
					{'#', '4', '5'},
					{'6', '7', '8'}})
			};
			vector<GameFieldData> actualMoves = field.getMoves();

			Assert::AreEqual(expectedMoves.size(), actualMoves.size());
			for (int i = 0; i < expectedMoves.size(); i++)
				Assert::IsTrue(expectedMoves[i] == actualMoves[i]);
		}

		TEST_METHOD(emptyCellInRightTopCorner)
		{
			GameFieldData field({
				{'#', '1', '2', '3'},
				{'4', '5', '6', '7'} });

			vector<GameFieldData> expectedMoves = {
				GameFieldData({
					{'4', '1', '2', '3'},
					{'#', '5', '6', '7'} }),
				GameFieldData({
					{'1', '#', '2', '3'},
					{'4', '5', '6', '7'} }),
			};
			vector<GameFieldData> actualMoves = field.getMoves();

			Assert::AreEqual(expectedMoves.size(), actualMoves.size());
			for (int i = 0; i < expectedMoves.size(); i++)
				Assert::IsTrue(expectedMoves[i] == actualMoves[i]);
		}

		TEST_METHOD(emptyCellInRightBottomCorner)
		{
			GameFieldData field({
				{'1', '2', '3', '4'},
				{'#', '5', '6', '7'} });

			vector<GameFieldData> expectedMoves = {
				GameFieldData({
					{'#', '2', '3', '4'},
					{'1', '5', '6', '7'} }),
				GameFieldData({
					{'1', '2', '3', '4'},
					{'5', '#', '6', '7'} }),
			};
			vector<GameFieldData> actualMoves = field.getMoves();

			Assert::AreEqual(expectedMoves.size(), actualMoves.size());
			for (int i = 0; i < expectedMoves.size(); i++)
				Assert::IsTrue(expectedMoves[i] == actualMoves[i]);
		}

		TEST_METHOD(emptyCellInLeftTopCorner)
		{
			GameFieldData field({
				{'1', '2', '3', '#'},
				{'4', '5', '6', '7'} });

			vector<GameFieldData> expectedMoves = {
				GameFieldData({
					{'1', '2', '3', '7'},
					{'4', '5', '6', '#'} }),
				GameFieldData({
					{'1', '2', '#', '3'},
					{'4', '5', '6', '7'} }),
			};
			vector<GameFieldData> actualMoves = field.getMoves();

			Assert::AreEqual(expectedMoves.size(), actualMoves.size());
			for (int i = 0; i < expectedMoves.size(); i++)
				Assert::IsTrue(expectedMoves[i] == actualMoves[i]);
		}

		
	};
}
