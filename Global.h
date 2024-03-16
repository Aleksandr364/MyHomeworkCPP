#pragma once
#include <stdint.h>

// создание типа "указатель на функцию" *FuncPtrType
typedef int (*FuncPtrType)(float);

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