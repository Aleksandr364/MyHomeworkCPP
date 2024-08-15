#include <iostream>
#include "NewFileH.h"
#include "Global.h"

// √лобальный массив.
int global_iDataArray_1_4[]{ 0, 42, -4, 10, 0, 55, -134, 0, 1, 6, -8, 4, 2, -1, 0, 7, 8, 3, 2, 10, 5, -1, -2, -6, -34, 0 };
const int global_iDataArray_Len_1_4 = sizeof(global_iDataArray_1_4) / sizeof(int);

float global_fDataArray_1_5[]{ 0, 42, -4, 10, 0, 55, -134, 0, 1, 6, -8, 4, 2, -1, 0, 7, 8, 3, 2, 10, 5, -1, -2, -6, -34, 0 };
const int global_fDataArray_Len_1_5 = sizeof(global_fDataArray_1_5) / sizeof(float);

const int GlobalMaxBuffLen = 128;

const char* FileName_global_iDataArray_1_4 = "global_iDataArray_1_4.txt";
const char* FileName_global_fDataArray_1_5 = "global_fDataArray_1_5.txt";

void TestFileWrite(const char* FileName, const char* buffer, int buffLen)
{
	FILE* file = nullptr;

	errno_t err = fopen_s(&file, FileName, "a+");

	if (err || !file) return;

	if (!buffLen) buffLen = (int)strlen(buffer);

	size_t realSize = fwrite(buffer, 1, buffLen, file);

	fclose(file);
}

void TestFileWriteBin(const char* FileName, int Number)
{
	FILE* file = nullptr;

	errno_t err = fopen_s(&file, FileName, "ab+");

	if (err || !file) return;

	size_t realSize = fwrite(&Number, 1, sizeof(int), file);

	fclose(file);
}

void TestFileWriteBinFloat(const char* FileName, float Number)
{
	FILE* file = nullptr;

	errno_t err = fopen_s(&file, FileName, "ab+");

	if (err || !file) return;

	size_t realSize = fwrite(&Number, 1, sizeof(float), file);

	fclose(file);
}

void FileWriteInt()
{
	char buffer[GlobalMaxBuffLen]{};

	for (int i = 0; i < global_iDataArray_Len_1_4; i++)
	{
		sprintf_s(buffer, GlobalMaxBuffLen, "%i\n", global_iDataArray_1_4[i]);
		TestFileWrite(FileName_global_iDataArray_1_4, buffer, int(strlen(buffer)));
	}
}

void FileWriteFloat()
{
	char buffer[GlobalMaxBuffLen]{};

	for (int i = 0; i < global_fDataArray_Len_1_5; i++)
	{
		sprintf_s(buffer, GlobalMaxBuffLen, "%f\n", global_fDataArray_1_5[i]);
		TestFileWrite("fData.txt", buffer, int(strlen(buffer)));
	}
}

void FileWriteIntBin()
{
	for (int i = 0; i < global_iDataArray_Len_1_4; i++)
	{
		TestFileWriteBin("global_iDataArray_1_4_BIN.txt", global_iDataArray_1_4[i]);
	}
}

void FileWriteFloatBin()
{
	for (int i = 0; i < global_fDataArray_Len_1_5; i++)
	{
		TestFileWriteBinFloat("fData_BIN.txt", global_fDataArray_1_5[i]);
	}
}

int* ReadBINFileInt(const char* FileName, int& FileLen)
{
	FILE* file = nullptr;

	errno_t err = fopen_s(&file, FileName, "rb");

	if (err || !file) return 0;

	// fseek() - перемещение внутри файла в указанную позицию (в данном случае устанавливаетс€ в последнюю позицию: "ноль от конца файла")
	fseek(file, 0, SEEK_END);

	// ftell() - возвращает текущую позицию в файле file  в виде числа
	int iSize = ftell(file);

	// дл€ дальнейшей работы снова возвращаем в начальное (нулевое) значению позицию в файле
	fseek(file, 0, SEEK_SET);

	FileLen = iSize / sizeof(int);

	int* iData = new int[FileLen+1] {};

	size_t realSize = fread(iData, 1, iSize, file); // buffer overrun???????????

	fclose(file);

	return iData;
}

float* ReadBINFileFloat(const char* FileName, int& FileLen)
{
	FILE* file = nullptr;

	errno_t err = fopen_s(&file, FileName, "rb");

	if (err || !file) return 0;

	// fseek() - перемещение внутри файла в указанную позицию (в данном случае устанавливаетс€ в последнюю позицию: "ноль от конца файла")
	fseek(file, 0, SEEK_END);

	// ftell() - возвращает текущую позицию в файле file  в виде числа
	int iSize = ftell(file);

	// дл€ дальнейшей работы снова возвращаем в начальное (нулевое) значению позицию в файле
	fseek(file, 0, SEEK_SET);

	FileLen = iSize / sizeof(float);

	float* fData = new float[FileLen+1] {};

	size_t realSize = fread(fData, 1, iSize, file); // buffer overrun?????????????

	fclose(file);

	return fData;
}

int FileReadGetLinesCount(const char* FileName)
{
	FILE* file = nullptr;

	errno_t err = fopen_s(&file, FileName, "r");

	if (err || !file) return 0;

	char line[128]{};

	int count = 0;
	// fgets() - читает одну строку символов из файла в буфер: char line[128]{}
	while (fgets(line, sizeof(line), file)) count++;

	fclose(file);

	return count;
}

int* ReadSymbolFileInt(const char* FileName, int& FileLen)
{
	FILE* file = nullptr;

	errno_t err = fopen_s(&file, FileName, "r");

	if (err || !file) return 0;

	int iSize = FileReadGetLinesCount(FileName);
	
	FileLen = iSize;

	int* iData = new int[FileLen+1] {};

	char line[128]{};

	int i = 0;
	while (fgets(line, sizeof(line), file))
	{
		iData[i++] = int(atoi(line));
	}

	fclose(file);

	return iData;
}

float* ReadSymbolFileFloat(const char* FileName, int& FileLen)
{
	FILE* file = nullptr;

	errno_t err = fopen_s(&file, FileName, "r");

	if (err || !file) return 0;

	int iSize = FileReadGetLinesCount(FileName);

	FileLen = iSize;

	float* fData = new float[FileLen+1] {};

	char line[128]{};

	int i = 0;
	while (fgets(line, sizeof(line), file))
	{
		fData[i++] = float(atof(line));
	}

	fclose(file);

	return fData;
}

size_t TestFileRead(const char* FileName, char* buffer, const int buffLen)
{
	FILE* file = nullptr;

	errno_t err = fopen_s(&file, FileName, "r");

	if (err || !file) return 0;

	size_t realSize = fread(buffer, 1, buffLen, file);

	fclose(file);

	return realSize;
}


TestStruct* TestFileReadStruct(const char* FileName)
{
	TestStruct* Struct = new TestStruct;
	FILE* file = nullptr; // указатель на дескриптор файла
	
	errno_t err = fopen_s(&file, FileName, "r"); // возвращает дескриптор &file

	if (err || !file) return 0;

	size_t realSize = fread(Struct, 1, sizeof(TestStruct), file);
	fclose(file); // файл необходимо ќЅя«ј“≈Ћ№Ќќ закрывать (после закрыти€ с ним нельз€ работать)
	
	if (realSize != sizeof(TestStruct)) return nullptr;
	return Struct;
}

int TestFileWriteStruct(const char* FileName)
{
	TestStruct Struct;

	Struct.x = -1;
	Struct.y = 2;

	my_strcpy(Struct.Name1, (char*)"Hello ");
	my_strcpy(Struct.Name2, (char*)"World!");

	FILE* file = nullptr; // указатель на дескриптор файла

	errno_t err = fopen_s(&file, FileName, "a+"); // возвращает дескриптор &file

	if (err || !file) return 0;

	size_t realSize = fwrite(&Struct, 1, sizeof(TestStruct), file);
	fclose(file); // файл необходимо ќЅя«ј“≈Ћ№Ќќ закрывать (после закрыти€ с ним нельз€ работать)
	
	if (realSize != sizeof(TestStruct)) return 0;
	return 1;
}

int TestFileWriteStruct2(TestStruct& Struct, const char* FileName)
{
	FILE* file = nullptr; // указатель на дескриптор файла

	errno_t err = fopen_s(&file, FileName, "a+"); // возвращает дескриптор &file

	if (err || !file) return 0;

	size_t realSize = fwrite(&Struct, 1, sizeof(TestStruct), file);
	fclose(file); // файл необходимо ќЅя«ј“≈Ћ№Ќќ закрывать (после закрыти€ с ним нельз€ работать)

	if (realSize != sizeof(TestStruct)) return 0;
	return 1;
}

void TestFileWriteStructArray(const char* FileName)
{
	TestStruct Struct;
	char Buffer[20]{};

	for (int i = 0; i < 10; i++)
	{
		Struct.x = i;
		Struct.y = i * i;
		my_strcpy(Struct.Name1, (char*)"Hello ");
		my_strcpy(Struct.Name2, (char*)"World!");
		sprintf_s(Buffer, "%i", i);
		my_strcat(Struct.Name1, Buffer);
		my_strcat(Struct.Name2, Buffer);
		TestFileWriteStruct2(Struct, FileName);
	}
}

size_t TestFileReadStruct2(TestStruct& Struct, const char* FileName, int poz)
{
	FILE* file = nullptr; // указатель на дескриптор файла

	errno_t err = fopen_s(&file, FileName, "r"); // возвращает дескриптор &file

	if (err || !file) return 0;

	fseek(file, poz, SEEK_SET); // смещение в файле от начала на poz байт

	size_t realSize = fread(&Struct, 1, sizeof(TestStruct), file);
	fclose(file); // файл необходимо ќЅя«ј“≈Ћ№Ќќ закрывать (после закрыти€ с ним нельз€ работать)

	return realSize;
}

void TestFileReadStructArray(const char* FileName)
{
	TestStruct Struct;

	int poz = 0;

	for (;;)
	{
		size_t realSize = TestFileReadStruct2(Struct, FileName, poz);
		if (!realSize)
			break;
		poz += (int)realSize;
		std::cout << "\n" << Struct.x << "\n" << Struct.y << "\n" << Struct.Name1 << "\n" << Struct.Name2 << "\n";
	}
}