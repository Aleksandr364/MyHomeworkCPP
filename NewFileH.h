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

#pragma pack(push) // �������� - ���������� ��������: push - ��������� ������� �������� (������������) 
#pragma pack(1) // ��������� �������� pack ������ ������� (������� = 1 ����, ���������� "������������" ��� ��������� 4)
struct ID3v24Header
{
	char ID[3]{};
	int8_t MajorVersion = 0;
	int8_t RevisionNumber = 0;
	int8_t Flags = 0;
	int32_t Size = 0;
};
#pragma pack(pop) // ������������ ���������� ������� ��������

ID3v24Header* ReadHeader(const char* FileName);