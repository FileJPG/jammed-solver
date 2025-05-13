#include "pch.h"
#include "CppUnitTest.h"
#include "../JammedSolver/JammedSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(Test_parseText)
	{
	public:
		
		TEST_METHOD(baseTest)
		{
			vector<string> text = {
				"abc",
				"sep",
				"def",
				"sep",
				"ghi"
			};
			string separator = "sep";

			vector<vector<string>> expectedTextBlocks = {
				{"abc"},
				{"def"},
				{"ghi"}
			};
			vector<vector<string>> actualTextBlocks = parseText(text, separator);

			Assert::AreEqual(expectedTextBlocks.size(), actualTextBlocks.size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				Assert::AreEqual(expectedTextBlocks[i].size(), actualTextBlocks[i].size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				for (int j = 0; j < expectedTextBlocks[i].size(); j++)
					Assert::AreEqual(expectedTextBlocks[i][j], actualTextBlocks[i][j]);
		}

		TEST_METHOD(manyStrings)
		{
			vector<string> text = {
				"abc",
				"sep",
				"def",
				"sep",
				"ghi",
				"sep",
				"abc",
				"sep",
				"def"
			};
			string separator = "sep";

			vector<vector<string>> expectedTextBlocks = {
				{"abc"},
				{"def"},
				{"ghi"},
				{"abc"},
				{"def"}
			};
			vector<vector<string>> actualTextBlocks = parseText(text, separator);

			Assert::AreEqual(expectedTextBlocks.size(), actualTextBlocks.size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				Assert::AreEqual(expectedTextBlocks[i].size(), actualTextBlocks[i].size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				for (int j = 0; j < expectedTextBlocks[i].size(); j++)
					Assert::AreEqual(expectedTextBlocks[i][j], actualTextBlocks[i][j]);
		}

		TEST_METHOD(oneStringWithoutSeparators)
		{
			vector<string> text = {
				"abc"
			};
			string separator = "sep";

			vector<vector<string>> expectedTextBlocks = {
				{"abc"}
			};
			vector<vector<string>> actualTextBlocks = parseText(text, separator);

			Assert::AreEqual(expectedTextBlocks.size(), actualTextBlocks.size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				Assert::AreEqual(expectedTextBlocks[i].size(), actualTextBlocks[i].size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				for (int j = 0; j < expectedTextBlocks[i].size(); j++)
					Assert::AreEqual(expectedTextBlocks[i][j], actualTextBlocks[i][j]);
		}

		TEST_METHOD(emptySeparatorString)
		{
			vector<string> text = {
				"abc",
				"",
				"def",
				"",
				"ghi"
			};
			string separator = "";

			vector<vector<string>> expectedTextBlocks = {
				{"abc"},
				{"def"},
				{"ghi"}
			};
			vector<vector<string>> actualTextBlocks = parseText(text, separator);

			Assert::AreEqual(expectedTextBlocks.size(), actualTextBlocks.size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				Assert::AreEqual(expectedTextBlocks[i].size(), actualTextBlocks[i].size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				for (int j = 0; j < expectedTextBlocks[i].size(); j++)
					Assert::AreEqual(expectedTextBlocks[i][j], actualTextBlocks[i][j]);
		}

		TEST_METHOD(noSeparatorsInText)
		{
			vector<string> text = {
				"abc",
				"def",
				"ghi"
			};
			string separator = "sep";

			vector<vector<string>> expectedTextBlocks = {
				{"abc", "def", "ghi"}
			};
			vector<vector<string>> actualTextBlocks = parseText(text, separator);

			Assert::AreEqual(expectedTextBlocks.size(), actualTextBlocks.size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				Assert::AreEqual(expectedTextBlocks[i].size(), actualTextBlocks[i].size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				for (int j = 0; j < expectedTextBlocks[i].size(); j++)
					Assert::AreEqual(expectedTextBlocks[i][j], actualTextBlocks[i][j]);
		}

		TEST_METHOD(onlySeparatorsInText)
		{
			vector<string> text = {
				"sep",
				"sep",
				"sep"
			};
			string separator = "sep";

			vector<vector<string>> expectedTextBlocks = {};
			vector<vector<string>> actualTextBlocks = parseText(text, separator);

			Assert::AreEqual(expectedTextBlocks.size(), actualTextBlocks.size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				Assert::AreEqual(expectedTextBlocks[i].size(), actualTextBlocks[i].size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				for (int j = 0; j < expectedTextBlocks[i].size(); j++)
					Assert::AreEqual(expectedTextBlocks[i][j], actualTextBlocks[i][j]);
		}

		TEST_METHOD(complexTest)
		{
			vector<string> text = {
				"abc",
				"sep",
				"sep",
				"def",
				"sep",
				"ghi",
				"",
				"sep"
			};
			string separator = "sep";

			vector<vector<string>> expectedTextBlocks = {
				{"abc"},
				{"def"},
				{"ghi", ""}
			};
			vector<vector<string>> actualTextBlocks = parseText(text, separator);

			Assert::AreEqual(expectedTextBlocks.size(), actualTextBlocks.size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				Assert::AreEqual(expectedTextBlocks[i].size(), actualTextBlocks[i].size());
			for (int i = 0; i < expectedTextBlocks.size(); i++)
				for (int j = 0; j < expectedTextBlocks[i].size(); j++)
					Assert::AreEqual(expectedTextBlocks[i][j], actualTextBlocks[i][j]);
		}

		
	};
}
