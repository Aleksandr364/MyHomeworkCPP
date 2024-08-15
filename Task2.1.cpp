#include <cmath>
#include <chrono>
#include <random>
#include <iostream>
#include "Global.h"

char* TestAllocMem(int64_t len, int64_t TailLen)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(32, 255);

	char* cLoc = new char[len+1] {};

	memset(cLoc, ' ', len);

	for (int64_t i = 0; i < len - TailLen; i++)
	{
		cLoc[i] = distribution(gen);
	}

	return cLoc;
}

char* CopyBuffer(char* buffer, int64_t len)
{
	char* cLoc = new char[len + 1] {};
	memcpy(cLoc, buffer, len);
	return cLoc;
}

bool isEven(int value)
{
	return value % 2;
}

bool isEven2(int value)
{
	// сохранить все биты и обнулить только младший
	// return value & 0xfffffffe;
	return value & 1;
}

float isEven3(float value)
{
	return (float)std::fmod(value, 2);
}

float getM(float value)
{
	return (float)std::fmod(value, 1);
}

void trimRight_simple1(char* str)
{
	if (!str) return;
	int len = (int)strlen(str);

	int i = len - 1;

	for (; i >= 0; i--)
	{
		if (str[i] == ' ') str[i] = 0;
		else break;
	}
}

void trimRight_simple2(char* str)
{
	if (!str) return;
	int len = (int)strlen(str);

	int i = len - 1;

	for (; i >= 0; i--)
	{
		if (str[i] != ' ') break;
	}

	str[i + 1] = 0;
}

void trimRight(char* str)
{
	if (!str) return;

	int n = -1; // индекс последнего непробельного символа

	for (int i = 0;; i++)
	{
		if (!str[i]) break;
		if (str[i] != ' ') n = i;
	}

	str[n+1] = 0;
}


void ChronoTest(int count, trimFuncType trimFunc, int64_t len, int64_t TailLen, std::string text)
{
	std::chrono::nanoseconds* ArrayTime = new std::chrono::nanoseconds[count]{};

	// начальное значение времени (нулевое)
	std::chrono::nanoseconds timeSum = std::chrono::nanoseconds::zero();
	
	char* buffer = TestAllocMem(len, TailLen);

	char* bufferCopy = CopyBuffer(buffer, len);

	for (int i = 0; i < count; i++)
	{
		auto start = std::chrono::steady_clock::now();
		(*trimFunc)(buffer);
		auto end = std::chrono::steady_clock::now();
		std::chrono::nanoseconds diff = end - start;
		timeSum += diff;
		ArrayTime[i] = diff;
		std::cout << ArrayTime[i] << "\n";
		memcpy(buffer, bufferCopy, len);
	}

	std::chrono::nanoseconds AverageTime = timeSum / count;

	// перевод из std::chrono::nanoseconds в double
	double dAverageTime = std::chrono::duration<double, std::nano>(AverageTime).count();

	std::cout << text << "\n";

	std::cout << dAverageTime << "\n\n";

	delete[] buffer;
	delete[] bufferCopy;
	delete[] ArrayTime;
}

