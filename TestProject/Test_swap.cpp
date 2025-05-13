#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_swap)
	{
	public:

		TEST_METHOD(successUp)
		{
			GameFieldData actualMove({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData expectedMove({
				{'1', '2', '3', '#'},
				{'5', '6', '7', '4'} });

			bool actualSuccess = actualMove.swap(up);

			Assert::AreEqual(true, actualSuccess);
			Assert::IsTrue(expectedMove.getField() == actualMove.getField());
		}

		TEST_METHOD(unsuccessDown)
		{
			GameFieldData actualMove({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData expectedMove({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			bool actualSuccess = actualMove.swap(down);

			Assert::AreEqual(false, actualSuccess);
			Assert::IsTrue(expectedMove.getField() == actualMove.getField());
		}

		TEST_METHOD(unsuccessRight)
		{
			GameFieldData actualMove({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData expectedMove({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });

			bool actualSuccess = actualMove.swap(right);

			Assert::AreEqual(false, actualSuccess);
			Assert::IsTrue(expectedMove.getField() == actualMove.getField());
		}

		TEST_METHOD(successLeft)
		{
			GameFieldData actualMove({
				{'1', '2', '3', '4'},
				{'5', '6', '7', '#'} });
			GameFieldData expectedMove({
				{'1', '2', '3', '4'},
				{'5', '6', '#', '7'} });

			bool actualSuccess = actualMove.swap(left);

			Assert::AreEqual(true, actualSuccess);
			Assert::IsTrue(expectedMove.getField() == actualMove.getField());
		}

		TEST_METHOD(successDownFromEdge)
		{
			GameFieldData actualMove({
				{'1', '2', '#', '3'},
				{'4', '5', '6', '7'} });
			GameFieldData expectedMove({
				{'1', '2', '6', '3'},
				{'4', '5', '#', '7'} });

			bool actualSuccess = actualMove.swap(down);

			Assert::AreEqual(true, actualSuccess);
			Assert::IsTrue(expectedMove.getField() == actualMove.getField());
		}

		TEST_METHOD(successRightFromEdge)
		{
			GameFieldData actualMove({
				{'1', '2', '#', '3'},
				{'4', '5', '6', '7'} });
			GameFieldData expectedMove({
				{'1', '2', '3', '#'},
				{'4', '5', '6', '7'} });

			bool actualSuccess = actualMove.swap(right);

			Assert::AreEqual(true, actualSuccess);
			Assert::IsTrue(expectedMove.getField() == actualMove.getField());
		}

		
	};
}
