#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

// ��� ������
enum ErrorType
{
	none, // ��� ������
	cantOpenReadFile, // ������� ���� ������ �������/���������
	cantCreateFile, // �������� ���� ������ �������
	incorrectEmptyCellsCount, // ������������ ���������� ������ ������ � �����������
	incorrectSymbolsInField, // ������������ ������ � �����������
	incorrectFieldSize,	// ������������ ������ �����������
	differentSymbolsSets, // ������ ����� � ��������� � ������� ������������
	incorrectFieldsCount // ������������ ���������� �����������
};

// ������
class Error
{
	// ��� ������
	ErrorType type;

	// ���� � �������� �����
	string filePath;
	
	// ��������������� ����������� �������� ���������
	bool isInitialField;

	// ������� ����-����
	int count;
	
	// ������������ �������
	vector<char> symbols;
	
	// ������� ����
	int fieldSizeX, fieldSizeY;
};
