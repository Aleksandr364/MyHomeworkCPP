#include <iostream>
#include "Global.h"
#include "NewFileH.h"

// примеры использования типа "указатель на функцию"
int FuncTest1(float x)
{
	return (int)x;
}
int FuncTest2(float x)
{
	return (int)x * 2;
}
FuncPtrType FuncArray[] = { FuncTest1, FuncTest2 };
int FuncArrayLen = sizeof(FuncArray) / sizeof(FuncPtrType);
void FuncTestMain1()
{
	FuncPtrType Func = FuncTest1;
	std::cout << "\n" << (*Func)(3.14f) << "\n";
	Func = FuncTest2;
	std::cout << (*Func)(3.14f) << "\n";

	for (int i = 0; i < FuncArrayLen; i++) std::cout << (*FuncArray[i])(3.14f) << "\n";
}

// задание переменной "указатель на функцию" без специально созданного типа
void FuncTestMain2()
{
	int (*FuncPtr)(float) = nullptr;

	FuncPtr = FuncTest1;
	std::cout << (*FuncPtr)(3.14f) << "\n";
}

void FuncTestMain3(FuncPtrType Func)
{
	std::cout << "\n" << (*Func)(3.14f) << "\n";
}





bool FloatEquality(float x, float y, float d)
{
	return x >= y - d && x <= y + d;
}

// strcpy_s(cText1, 10, "Dfg");
// Классическое strcpy выглядит так: strcpy(destination, source).
char* my_strcpy(char* destination, char* source)
{
	char* temp = destination;
	// цикл копирования строки целиком:
	while (*destination++ = *source++);
	return temp;
}

void* my_memcpy(void* destination, const void* source, size_t num)
{
	char* to = (char*)destination;
	char* from = (char*)source;
	while (num--) *to++ = *from++;
	return to;
}

size_t my_strlen(const char* str)
{
	size_t i = 0;
	while (*str++) i++;
	return i;
}

// рекурсивная функция для факториала
int64_t Factorial(int n)
{
	if (n == 1) return 1;
	else return n * Factorial(n - 1);
}

// факториал без рекурсии
int64_t FactorialWithoutRec(int n)
{
	int64_t iRes = 1;

	for (int i = 1; i <= n; i++)
		iRes *= i;

	return iRes;
}

char* my_strcat(char* destination, const char* source)
{
	char* cBeginning = destination;
	while (*destination != '\0') destination++;
	while (*destination++ = *source++);
	return cBeginning;
}

int my_strcmp(const char* str1, const char* str2)
{
	while (*str1 == *str2 && *str1 != '\0')
	{
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

int my_memcmp(const void* ptr1, const void* ptr2, size_t num)
{
	char* newPtr1 = (char*)ptr1;
	char* newPtr2 = (char*)ptr2;
	while (*newPtr1 == *newPtr2 && num > 0)
	{
		newPtr1++;
		newPtr2++;
		num--;
	};
	return *newPtr1 - *newPtr2;
}

int my_stricmp(const char* str1, const char* str2)
{
	int iStr1 = 0;
	int iStr2 = 0;
	while (*str1 != '\0')
	{
		if (*str1 != *str2)
		{
			if (*str1 >= 'A' && *str1 <= 'Z') iStr1 = *str1 + ('a' - 'A');
			else iStr1 = *str1;
			if (*str2 >= 'A' && *str2 <= 'Z') iStr2 = *str2 + ('a' - 'A');
			else iStr2 = *str2;
			if (iStr1 != iStr2) return iStr1 - iStr2;
			else
			{
				str1++;
				str2++;
			};
		}
		else
		{
			str1++;
			str2++;
		}
	}
	if (*str1 >= 'A' && *str1 <= 'Z') iStr1 = *str1 + ('a' - 'A');
	else iStr1 = *str1;
	if (*str2 >= 'A' && *str2 <= 'Z') iStr2 = *str2 + ('a' - 'A');
	else iStr2 = *str2;
	return iStr1 - iStr2;
}

int my_memicmp(const void* ptr1, const void* ptr2, size_t num)
{
	char* newPtr1 = (char*)ptr1;
	char* newPtr2 = (char*)ptr2;
	int iStr1 = 0;
	int iStr2 = 0;
	while (*newPtr1 != '\0' && num > 0)
	{
		if (*newPtr1 != *newPtr2)
		{
			if (*newPtr1 >= 'A' && *newPtr1 <= 'Z') iStr1 = *newPtr1 + ('a' - 'A');
			else iStr1 = *newPtr1;
			if (*newPtr2 >= 'A' && *newPtr2 <= 'Z') iStr2 = *newPtr2 + ('a' - 'A');
			else iStr2 = *newPtr2;
			if (iStr1 != iStr2) return iStr1 - iStr2;
			else
			{
				newPtr1++;
				newPtr2++;
				num--;
			};
		}
		else
		{
			newPtr1++;
			newPtr2++;
			num--;
		}
	}
	if (*newPtr1 >= 'A' && *newPtr1 <= 'Z') iStr1 = *newPtr1 + ('a' - 'A');
	else iStr1 = *newPtr1;
	if (*newPtr2 >= 'A' && *newPtr2 <= 'Z') iStr2 = *newPtr2 + ('a' - 'A');
	else iStr2 = *newPtr2;
	return iStr1 - iStr2;
}

// функция меняет местами байты внутри 4-байтового целого: 0 -> 3, 1 -> 2.
uint32_t ExchangeDWbytes(uint8_t b[4])
{
	return (b[3]) | (b[2] << 8) | (b[1] << 16) | (b[0] << 24);
}

// приводит размер mp3 к "человеческому" формату
uint32_t AdjustSize(uint32_t dwSize)
{
	dwSize &= 0x7F7F7F7F;
	return ExchangeDWbytes((uint8_t*)&dwSize);
}

ID3v24Header* ReadHeader(const char* FileName)
{
	FILE* file = nullptr;

	fopen_s(&file, FileName, "rb"); // "rb" - бинарный режим чтения для любых НЕ текстовых файлов: изображения, звуковые, exe и тд.

	if (!file) return nullptr;

	ID3v24Header* pID3v24Header = new ID3v24Header;

	size_t RealSize = fread(pID3v24Header, 1, sizeof(ID3v24Header), file);

	fclose(file);

	if (RealSize != sizeof(ID3v24Header)) return nullptr;
	
	pID3v24Header->Size = AdjustSize(pID3v24Header->Size);

	return pID3v24Header;
}

