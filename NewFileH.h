#pragma once

#include <stdio.h>
#include <string.h>

typedef unsigned char byte;
typedef unsigned long long int qword;

void TestFileWrite(const char* FileName, const char* buffer, int buffLen = 0);
size_t TestFileRead(const char* FileName, char* buffer, const int buffLen);

struct TestStruct
{
	int x = 0;
	int y = 1;
	char Name1[20]{};
	char Name2[10]{};
};

int TestFileWriteStruct(const char* FileName);
TestStruct* TestFileReadStruct(const char* FileName);

void TestFileWriteStructArray(const char* FileName);
void TestFileReadStructArray(const char* FileName);
size_t TestFileReadStruct2(TestStruct& Struct, const char* FileName, int poz);
int TestFileWriteStruct2(TestStruct& Struct, const char* FileName);

#pragma pack(push) // упаковка - размещение структур: push - сохранить текущее значение (препроцессор) 
#pragma pack(1) // установка значения pack равная единице (граница = 1 байт, отменяется "выравнивание" под кратность 4)
struct ID3v24Header
{
	char ID[3]{};
	int8_t MajorVersion = 0;
	int8_t RevisionNumber = 0;
	int8_t Flags = 0;
	int32_t Size = 0;
};
#pragma pack(pop) // восстановить предыдущую границу упаковки

ID3v24Header* ReadHeader(const char* FileName);

void FileWriteInt();
void TestFileWriteBin(const char* FileName, int Number);
void FileWriteIntBin();
int* ReadBINFileInt(const char* FileName, int& FileLen);
void Cout_Function(std::string Text, int* Array, int iLen);
int* ReadSymbolFileInt(const char* FileName, int& FileLen);

void TestFileWriteBinFloat(const char* FileName, float Number);
void FileWriteFloat();
void FileWriteFloatBin();
float* ReadBINFileFloat(const char* FileName, int& FileLen);
float* ReadSymbolFileFloat(const char* FileName, int& FileLen);
