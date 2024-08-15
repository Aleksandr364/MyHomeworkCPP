#pragma once

int GetRandomNumberInt(int, int);
float GetRandomNumberFloat(float, float);

int GetArrMinValAndMinIdx(int*, int, int&);
void Task1_2_1();

int GetArrMinSecondVal2pass(int*, int);
void Task1_2_2();

int GetArrMinSecondVal1pass(int*, int, int&);
void Task1_2_3();

int* GetNegArrItems(int*, int, int&);
void Task1_2_4();

int* SeparateNegAndPosItems2pass(int*, int, int&);
void Task1_2_5();

int GetNextNegItemIdx(int*&, int, int);
void Task1_2_6();

void SeparateNegAndPosItems1pass(int*&, const int);
void Task1_3_1();

int GetFirstUniqueItem(int*, int, int&);
void Task1_3_2();

void GetTwoFirstUniqueItems(int*, int, int&, int&);
void Task1_3_3();

void ReverseArrInSitu(int*&, int);
void Task1_3_4();

int* ReverseArr(int*, int);
void Task1_3_5();

void ReverseArrInSituHalves(int*&, int);
void ReverseArrInSituHalves2(int*&, int);
void Task1_3_6();

void ReverseNegItemsInSitu(int*&, int);
void Task1_3_7();

int* CreateRandIntArr(int, int, int);
void Task1_3_8();

float* CreateRandFloatArr(int, float, float);
void Task1_3_9();

int* SelectTensZero(int*, int, int&);
void Task1_3_10();

void ArrCyclicShiftLeft(int*&, int);
void Task1_3_11();

void ArrCyclicShiftRight(int*&, int);
void Task1_3_12();


void TestArray2D();



void TestFunc_1();

void TestFunc_2();

void TestCrash(int);