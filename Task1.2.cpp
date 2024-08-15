#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <limits>

using namespace std;

// глобальный массив
int global_iDataArray[]{1, 6, -8, 4, 2, -1, 0, 7, 8, 3, 2, 10, 5, -1, -2, -6, -34, 0};
const int global_iDataArray_Len = sizeof(global_iDataArray) / sizeof(int);

// Задача 1.

int GetArrMinValAndMinIdx(int* iData, int iLen, int& iMinIdx)
{
	// переменная для индекса минимального элемента массива iData
	iMinIdx = -1;

	if (!iData || !iLen) return 0;

	// переменная для минимального элемента массива iData
	int Min_of_iData = std::numeric_limits<int>::max(); // максимально возможное число типа Int

	for (int i = 0; i < iLen; i++)
	{
		if (Min_of_iData > iData[i])
		{
			Min_of_iData = iData[i];
			iMinIdx = i;
		}
	}

	return Min_of_iData;
}

int GetArrMinVal(int* iData, int iLen)
{
	if (!iData || !iLen) return 0;

	// переменная для индекса минимального элемента массива iData
	int iMinIdx = 0;

	return GetArrMinValAndMinIdx(iData, iLen, iMinIdx);
}

void Task1_2_1()
{
	// определяем длину массива iData через задание iLen
	int iLen = 0;
	cout << "Task 1: Min of iData and iMinIdx.\n";
	cout << "iData Length: iLen = ";
	cin >> iLen;

	if (iLen == 0) return;

	// объявление массива iData
	int* iData = new int[iLen] {0};

	// задание элементов массива iData
	for (int i = 0, k = 0; i < iLen; i++)
	{
		cout << "iData[" << i << "] = ";
		cin >> k;
		iData[i] = k;
		k = 0;
	}

	// локальный блок {}
	{
		// переменная для индекса минимального элемента массива iData
		int iMinIdx = 0;
		// переменная для минимального элемента массива iData
		int Min_of_iData = GetArrMinValAndMinIdx(iData, iLen, iMinIdx);

		// вывод результата через значения переменных Min_of_iData и iMinIdx
		cout << "Min of iData = " << Min_of_iData << "\n";
		cout << "iMinIdx = " << iMinIdx << "\n";
	}

	// очистка памяти
	delete[]iData;
}

// Задача 2.

int GetArrMinSecondVal2pass(int* iData, int iLen)
{
	if (!iData || !iLen) return 0;

	// переменная для индекса минимального элемента массива iData
	int iMinIdx = 0;
	// переменная для минимального элемента массива iData
	int Min_of_iData = std::numeric_limits<int>::max();
	
	// поиск индекса минимального элемента массива iData
	for (int i = 0; i < iLen; i++)
	{
		if (Min_of_iData > iData[i])
		{
			Min_of_iData = iData[i];
			iMinIdx = i;
		}
	}

	// "устранение" минимального элемента массива
	iData[iMinIdx] = numeric_limits<int>::max();

	// переменная для второго минимального элемента массива iData
	int Second_Min_of_iData = std::numeric_limits<int>::max();

	// поиск второго минимального элемента массива iData
	for (int i = 0; i < iLen; i++)
	{
		if (Second_Min_of_iData > iData[i])
		{
			Second_Min_of_iData = iData[i];
		}
	}

	return Second_Min_of_iData;
}

void Task1_2_2()
{
	// определяем длину массива iData через задание iLen
	int iLen = 0;
	cout << "\nTaks 2: Second Min of iData.\n";
	cout << "iData Length: iLen = ";
	cin >> iLen;

	if (iLen < 2) return;

	// объявление массива iData
	int* iData = new int[iLen] {0};

	// задание элементов массива iData
	for (int i = 0, k = 0; i < iLen; i++)
	{
		cout << "iData[" << i << "] = ";
		cin >> k;
		iData[i] = k;
		k = 0;
	}

	// переменная для второго минимального элемента массива iData
	int Second_Min_of_iData = GetArrMinSecondVal2pass(iData, iLen);

	// вывод результата через значение переменной Second_Min_of_iData
	cout << "Second_Min_of_iData = " << Second_Min_of_iData << "\n";

	// очистка памяти
	delete[]iData;
}

// Задача 2_1

int GetArrMinSecondVal2pass_2(int* iData, int iLen)
{
	if (!iData || !iLen) return 0;

	// переменная для минимального элемента массива iData
	int Min_of_iData = GetArrMinVal(iData, iLen);

	// переменная для второго минимального элемента массива iData
	int Second_Min_of_iData = std::numeric_limits<int>::max();

	// поиск второго минимального элемента массива iData
	for (int i = 0; i < iLen; i++)
		if (Min_of_iData < iData[i] && Second_Min_of_iData > iData[i])
			Second_Min_of_iData = iData[i];

	if (Second_Min_of_iData == numeric_limits<int>::max()) Second_Min_of_iData = Min_of_iData;

	return Second_Min_of_iData;
}

void Task1_2_2_1()
{
	// переменная для второго минимального элемента массива iData
	int Second_Min_of_iData = GetArrMinSecondVal2pass_2(global_iDataArray, global_iDataArray_Len);

	// вывод результата через значение переменной Second_Min_of_iData
	cout << "Second_Min_of_iData = " << Second_Min_of_iData << "\n";
}

// Задача 3.

int GetArrMinSecondVal1pass(int* iData, int iLen, int& Second_Min_of_iData)
{
	if (!iData || !iLen) return 0;

	// переменная для минимального элемента массива iData
	int Min_of_iData = std::numeric_limits<int>::max();

	for (int i = 0; i < iLen; i++)
	{
		if (Min_of_iData > iData[i])
		{
			Second_Min_of_iData =  Min_of_iData;
			Min_of_iData = iData[i];
		}
		if (Min_of_iData < iData[i] && Second_Min_of_iData > iData[i]) Second_Min_of_iData = iData[i];
	}

	return Min_of_iData;
}

void Task1_2_3()
{
	// переменная для второго минимального элемента массива iData
	int Second_Min_of_iData = 0;
	// переменная для минимального элемента массива iData
	int Min_of_iData = GetArrMinSecondVal1pass(global_iDataArray, global_iDataArray_Len, Second_Min_of_iData);

	// вывод результата через значения переменных Min_of_iData и Second_Min_of_iData
	cout << "Min of iData = " << Min_of_iData << "\n";
	cout << "Second Min of iData = " << Second_Min_of_iData << "\n";
}

// Задача 4.

int* GetNegArrItems(int* iData, int iLen, int& iOutLen)
{
	if (!iData) return nullptr;
	
	// находим размер массива iOut, считая кол-во отриц. эл-ов в массиве iData
	for (int i = 0; i < iLen; i++)
	{
		if (iData[i] < 0) iOutLen++;
	}

	// если кол-во отриц. эл-ов iData равно 0, тогда возвращает iOut с 0, а iOutLen = 1
	if (iOutLen == 0)
	{
		int* iOut = new int[1] {0};
		iOutLen = 1;
		return iOut;
	}
	else
	{
		int* iOut = new int[iOutLen] {};

		// заполняем iOut элементами
		for (int i = 0, k = 0; i < iLen; i++)
		{
			if (iData[i] < 0)
			{
				iOut[k] = iData[i];
				k++;
			}
		}
		return iOut;
	}
}

int* GetNegArrItems_2(int* iData, int iLen, int& iOutLen)
{
	if (!iData) return nullptr;

	vector<int> intVector;

	for (int i = 0; i < iLen; i++)
		if (iData[i] < 0)
			intVector.push_back(iData[i]);

	int Size_of_intVector = sizeof(intVector);
	
	iOutLen = (int)intVector.size();

	int* iOut = new int[iOutLen] {};

	for (int i = 0; i < iOutLen; i++)
		iOut[i] = intVector[i];

	return iOut;
}

void Task1_2_4()
{
	// переменная для числа элементов массива iOut
	int iOutLen = 0;
	// массив iOut
	int* iOut = GetNegArrItems_2(global_iDataArray, global_iDataArray_Len, iOutLen);

	// вывод результата: кол-во эл-ов массива iOut и сам массив
	cout << "iOutLen = " << iOutLen << "\n";
	cout << "iOut:" << "\n";
	for (int i = 0; i < iOutLen; i++)
	{
		cout << "iOut[" << i << "] = " << iOut[i] << "\n";
	}

	delete[] iOut;
}

// Задача 5.

int* SeparateNegAndPosItems2pass(int* iData, int iLen, int& iOutLen)
{
	if (!iData) return nullptr;

	// находим размер массива iOut, считая кол-во не нулевых эл-ов в массиве iData
	for (int i = 0; i < iLen; i++)
	{
		if (iData[i] != 0) iOutLen++;
	}

	// если кол-во эл-ов iOutLen равно 0, тогда возвращает iOut с 0, а iOutLen = 1
	if (iOutLen == 0)
	{
		int* iOut = new int[1] {0};
		iOutLen = 1;
		return iOut;
	}
	else
	{
		int* iOut = new int[iOutLen] {0};

		// заполняем iOut элементами
		for (int i = 0, j = 0, k = iOutLen - 1; i < iLen; i++)
		{
			if (iData[i] < 0)
			{
				iOut[j] = iData[i];
				j++;
			}
			if (iData[i] > 0)
			{
				iOut[k] = iData[i];
				k--;
			}
		}

		return iOut;
	}
}

void Task1_2_5()
{
	// переменная для числа элементов массива iOut
	int iOutLen = 0;
	// массив iOut
	int* iOut = SeparateNegAndPosItems2pass(global_iDataArray, global_iDataArray_Len, iOutLen);

	// вывод массива iOut
	cout << "iOut:" << "\n";
	for (int i = 0; i < iOutLen; i++)
	{
		cout << "iOut[" << i << "] = " << iOut[i] << "\n";
	}

	delete[]iOut;
}

// Задача 6.

int GetNextNegItemIdx(int*& iData, int iBegIdx, int iLen)
{
	int iBegIdxClose_1 = -1;
	int iBegIdxClose_2 = -1;

	for (int i = iBegIdx; i < iLen; i++)
	{
		if (iData[i] < 0)
		{
			iBegIdxClose_1 = i;
			break;
		}
	}
	for (int j = iBegIdx; j >= 0; j--)
	{
		if (iData[j] < 0)
		{
			iBegIdxClose_2 = j;
			break;
		}
	}

	if (iBegIdxClose_1 == -1 && iBegIdxClose_2 == -1) return -1;
	if (iBegIdxClose_1 == -1 && iBegIdxClose_2 != -1) return iBegIdxClose_2;
	if (iBegIdxClose_1 != -1 && iBegIdxClose_2 == -1) return iBegIdxClose_1;
	else
	{
		if (abs(iBegIdx - iBegIdxClose_1) > abs(iBegIdx - iBegIdxClose_2)) return iBegIdxClose_2;
		if (abs(iBegIdx - iBegIdxClose_1) < abs(iBegIdx - iBegIdxClose_2)) return iBegIdxClose_1;
		if (abs(iBegIdx - iBegIdxClose_1) == abs(iBegIdx - iBegIdxClose_2)) return -1 * (iBegIdxClose_1 + iBegIdxClose_2);
		else return -1;
	}
}

int GetNextNegItemIdx_2(int*& iData, int iBegIdx, int iLen)
{
	for (int i = iBegIdx; i < iLen; i++)
		if (iData[i] < 0)
			return i;

	return -1;
}

void Task1_2_6()
{
	// определяем длину массива iData через задание iLen
	int iLen = 0;
	cout << "\nTask 6: iBegIdxClose.\n";
	cout << "iData Length: iLen = ";
	cin >> iLen;

	if (iLen == 0) return;

	// объявление массива iData
	int* iData = new int[iLen] {0};

	// задание элементов массива iData
	for (int i = 0, k = 0; i < iLen; i++)
	{
		cout << "iData[" << i << "] = ";
		cin >> k;
		iData[i] = k;
		k = 0;
	}

	// задать iBegIdx
	int iBegIdx = 0;
	cout << "iBegIdx = ";
	cin >> iBegIdx;

	if (iBegIdx < 0 || iBegIdx >= iLen)
	{
		// очистка памяти
		delete[]iData;
		return;
	}
	
	// находим iBegIdxClose
	int iBegIdxClose = GetNextNegItemIdx(iData, iBegIdx, iLen);
	// вывод iBegIdxClose
	if (iBegIdxClose >= -1) cout << "iBegIdxClose = " << iBegIdxClose;
	if (iBegIdxClose < -1) cout << "iBegIdxClose = -1 * (iBegIdxClose_i + iBegIdxClose_j) = " << iBegIdxClose;

	// очистка памяти
	delete[]iData;
}