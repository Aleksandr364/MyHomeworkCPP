#include <iostream>
#include "NewFileH.h"
#include "Global.h"

void TestFileWrite(const char* FileName, const char* buffer, int buffLen)
{
	FILE* file = nullptr;

	errno_t err = fopen_s(&file, FileName, "a+");

	if (err || !file) return;

	if (!buffLen) buffLen = (int)strlen(buffer);

	size_t realSize = fwrite(buffer, 1, buffLen, file);

	fclose(file);
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