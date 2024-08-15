#pragma once
#include <stdint.h>

#define TIMEARRAYSIZE 30

// создание типа "указатель на функцию" *FuncPtrType
typedef int (*FuncPtrType)(float);
typedef void (*trimFuncType)(char*);

int FuncTest1(float x);
int FuncTest2(float x);
void FuncTestMain1();

void FuncTestMain2();
void FuncTestMain3(FuncPtrType Func);


const float delta = 0.001f;

bool FloatEquality(float, float, float = delta);

char* my_strcpy(char* destination, char* source);

void* my_memcpy(void* destination, const void* source, size_t num);

size_t my_strlen(const char* str);


int64_t Factorial(int n);


int64_t FactorialWithoutRec(int n);

char* my_strcat(char* destination, const char* source);

int my_strcmp(const char* str1, const char* str2);

int my_memcmp(const void* ptr1, const void* ptr2, size_t num);

int my_stricmp(const char* str1, const char* str2);

int my_memicmp(const void* ptr1, const void* ptr2, size_t num);

char* ReadBINFile(const char* fileName, int& fileLen);
int FileReadGetLinesCount(const char* FileName);

bool isEven(int value);
bool isEven2(int value);
float isEven3(float value);
float getM(float value);

void trimRight_simple1(char* str);
void trimRight_simple2(char* str);
void trimRight(char* str);

char* TestAllocMem(int64_t len, int64_t TailLen);

char* CopyBuffer(char* buffer, int64_t len);
void ChronoTest(int count, trimFuncType trimFunc, int64_t len, int64_t TailLen, std::string text);

