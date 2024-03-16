#pragma once

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

// ���������� ������.
int global_iDataArray_1_3[]{ 0, 42, -4, 10, 0, 55, -134, 0, 1, 6, -8, 4, 2, -1, 0, 7, 8, 3, 2, 10, 5, -1, -2, -6, -34, 0 };
const int global_iDataArray_Len_1_3 = sizeof(global_iDataArray_1_3) / sizeof(int);

// ����������� ������� #1.
int* CopyArray1(int* iData, int iLen)
{
	int* Array = new int[iLen] {};

	for (int i = 0; i < iLen; i++)
		Array[i] = iData[i];

	return Array;
}
// ����������� ������� #2.
int* CopyArray2(int* iData, int iLen)
{
	int* Array = new int[iLen] {};

	memcpy(Array, iData, sizeof(int) * iLen);

	return Array;
}
// ����������� ������� #3.
void CopyArray3(int* iData, int* Array, int iLen)
{
	for (int i = 0; i < iLen; i++)
		Array[i] = iData[i];
}

// ��������� ���������� int ������ ����� � ��������� [a, b] �� ����������� ���������� �++.
#include <random>
int GetRandomNumberInt(int a, int b)
{
	// ��������� ���������� "����������" �������� ��� ���������� ����������� ��� ������ ����������� ����������� ���������� �� ����������� ���������� C++.
	std::random_device rd;
	// ���� �� ����������� ��������� ����� �� ����������� ���������� C++ �� ������ "����������" ��������, ����������� � std::random_device rd.
	std::mt19937 gen(rd());
	// ����������� ������������� ��������� �����, ���������� � std::mt19937 gen(rd()), � �������� ��������� [a, b] �� ����������� ���������� C++.
	std::uniform_int_distribution<int> distribution(a, b);

	// ���� ��������� ���������� ����� � ��������� [a, b].
	return distribution(gen);
}
// ��������� ���������� float ����� � ��������� ������ � ��������� [a, b] �� ����������� ���������� �++.
#include <random>
float GetRandomNumberFloat(float a, float b)
{
	// ��������� ���������� "����������" �������� ��� ���������� ����������� ��� ������ ����������� ����������� ���������� �� ����������� ���������� C++.
	std::random_device rd;
	// ���� �� ����������� ��������� ����� �� ����������� ���������� C++ �� ������ "����������" ��������, ����������� � std::random_device rd.
	std::mt19937 gen(rd());
	// ����������� ������������� ��������� �����, ���������� � std::mt19937 gen(rd()), � �������� ��������� [a, b] �� ����������� ���������� C++.
	std::uniform_real_distribution<float> distribution(a, b);

	// ���� ��������� ���������� ����� � ��������� [a, b].
	return distribution(gen);
}

// ������� 1.
void SeparateNegAndPosItems1pass(int*& iData, int iLen)
{
	// ���� "������������" ������ �����-�������
	for (int i = 0, k = iLen - 1; i < k; i++)
	{
		// �������� "������" �������� �������
		if (iData[i] > 0)
		{
			int x = iData[i];

			// ���� "������������" ������ ������-������
			for (k; k > i; k--)
			{
				if (iData[k] < 0)
				{
					iData[i] = iData[k];
					iData[k] = x;
					break;
				}
			}
		}
	}
}
void Task1_3_1()
{
	int* iData = global_iDataArray_1_3;
	int iLen = global_iDataArray_Len_1_3;

	SeparateNegAndPosItems1pass(iData, iLen);

	cout << "Task1_3_1.\n";
	cout << "iData:" << "\n";
	for (int i = 0; i < iLen; i++)
	{
		cout << "[" << i << "] = " << global_iDataArray_1_3[i] << "\n";
	}
}

// ������� 2.
int GetFirstUniqueItem(int* iData, int iLen, int& iOutIdx)
{
	for (int i = iOutIdx; i < iLen - 1; i++)
	{
		int FirstUniqueItem = iData[i];

		for (int j = i + 1; j < iLen; j++)
		{
			if (FirstUniqueItem == iData[j]) break;
			if (j == iLen - 1 && FirstUniqueItem != iData[j])
			{
				iOutIdx = i;
				return FirstUniqueItem;
			}
		}
	}

	iOutIdx = -1;
	return std::numeric_limits<int>::max();
}
void Task1_3_2()
{
	int* iData = global_iDataArray_1_3;
	int iLen = global_iDataArray_Len_1_3;

	int iOutIdx = 0;
	int FirstUniqueItem = 0;

	cout << "\nTask1_3_2.\n";

	FirstUniqueItem = GetFirstUniqueItem(iData, iLen, iOutIdx);

	cout << "FirstUniqueItem: " << FirstUniqueItem << ".\n";
	cout << "iOutIdx: " << iOutIdx << ".\n";
}

// ������� 3.
void GetTwoFirstUniqueItems(int* iData, int iLen, int& iUniqueVal1, int& iUniqueVal2)
{
	iUniqueVal1 = std::numeric_limits<int>::max();
	iUniqueVal2 = std::numeric_limits<int>::max();

	int i = 0;
	int j = 0;

	int FirstUniqueItem = 0;

	for (i; i < iLen - 1; i++)
	{
		FirstUniqueItem = iData[i];

		j = i + 1;

		for (j; j < iLen; j++)
		{
			if (FirstUniqueItem == iData[j]) break;
		}

		if (FirstUniqueItem != iData[j])
		{
			iUniqueVal1 = FirstUniqueItem;
			break;
		}
	}
	
	int SecondUniqueItem = 0;

	i++;

	for (i; i < iLen - 1; i++)
	{
		SecondUniqueItem = iData[i];

		j = i + 1;

		for (j; j < iLen; j++)
		{
			if (SecondUniqueItem == iData[j]) break;
		}

		if (SecondUniqueItem != iData[j])
		{
			iUniqueVal2 = SecondUniqueItem;
			break;
		}
	}
}
void GetTwoFirstUniqueItems2(int* iData, int iLen, int& iUniqueVal1, int& iUniqueVal2)
{
	iUniqueVal1 = std::numeric_limits<int>::max();
	iUniqueVal2 = std::numeric_limits<int>::max();

	int iOutIdx = 0;

	iUniqueVal1 = GetFirstUniqueItem(iData, iLen, iOutIdx);

	if (iOutIdx == -1) return;

	iOutIdx++;

	iUniqueVal2 = GetFirstUniqueItem(iData, iLen, iOutIdx);
}
void Task1_3_3()
{
	int* iData = global_iDataArray_1_3;
	int iLen = global_iDataArray_Len_1_3;

	int iUniqueVal1 = 0;
	int iUniqueVal2 = 0;

	cout << "\nTask1_3_3.\n";

	GetTwoFirstUniqueItems2(iData, iLen, iUniqueVal1, iUniqueVal2);

	cout << "iUniqueVal1: " << iUniqueVal1 << ".\n";
	cout << "iUniqueVal2: " << iUniqueVal2 << ".\n";
}

// ������� 4.
void ReverseArrInSitu(int*& iData, int iLen)
{
	int i = 0;
	int k = iLen - 1;

	int x = 0;

	for (i; i < k; i++)
	{
		x = iData[i];
		iData[i] = iData[k];
		iData[k] = x;
		k--;
	}
}
void Task1_3_4()
{
	int* iData = global_iDataArray_1_3;
	int iLen = global_iDataArray_Len_1_3;

	ReverseArrInSitu(iData, iLen);

	cout << "\nTask1_3_4.\n";

	cout << "iData:" << "\n";
	for (int i = 0; i < iLen; i++)
	{
		cout << "[" << i << "] = " << global_iDataArray_1_3[i] << "\n";
	}
}

// ������� 5.
int* ReverseArr(int* iData, int iLen)
{
	int* Array = new int[iLen] {};

	for (int i = 0, k = iLen - 1; i < k; i++, k--)
	{
		Array[i] = iData[k];
		Array[k] = iData[i];
	}

	return Array;
}
void Task1_3_5()
{
	int* iData = global_iDataArray_1_3;
	int iLen = global_iDataArray_Len_1_3;

	int* Array1 = ReverseArr(iData, iLen);

	cout << "\nTask1_3_5.\n";

	cout << "iData:" << "\n";
	for (int i = 0; i < iLen; i++)
	{
		cout << "[" << i << "] = " << Array1[i] << "\n";
	}

	delete[] Array1;

	int Array2[10]{};

	CopyArray3(iData, Array2, 10);

	int* Array3 = new int[iLen] {};

	CopyArray3(iData, Array3, iLen);

	// CopyArray4(CopyArray3(iData, Array3, iLen)); ���� CopyArray3 ������������ int*

	delete[] Array3;
}

// ������� 6. �������� ��� 1-�� � 2-�� ������� �������.
void ReverseArrInSituHalves(int*& iData, int iLen)
{
	for (int i = 0, j = (iLen / 2) - 1, x = 0; i < j; i++, j--)
	{
		x = iData[i];
		iData[i] = iData[j];
		iData[j] = x;
	}

	for (int k = iLen / 2, l = iLen - 1, y = 0; k < l; k++, l--)
	{
		y = iData[k];
		iData[k] = iData[l];
		iData[l] = y;
	}
}
void ReverseArrInSituHalves2(int*& iData, int iLen)
{
	int iLenFirstHalf = iLen / 2;

	int iLenSecondHalf = iLen - iLenFirstHalf;

	ReverseArrInSitu(iData, iLenFirstHalf);

	int* iDataSecondHalf = iData + iLenFirstHalf;

	ReverseArrInSitu(iDataSecondHalf, iLenSecondHalf);
}
void Task1_3_6()
{
	int* iData = global_iDataArray_1_3;
	int iLen = global_iDataArray_Len_1_3;

	ReverseArrInSituHalves2(iData, iLen);

	cout << "\nTask1_3_6.\n";

	cout << "iData:" << "\n";
	for (int i = 0; i < iLen; i++)
	{
		cout << "[" << i << "] = " << global_iDataArray_1_3[i] << "\n";
	}
}

// ������� 7. �������� ������ ��� ������������� ��������� �������.
void ReverseNegItemsInSitu(int*& iData, int iLen)
{
	// ���� "������������" ������ �����-�������
	for (int i = 0, k = iLen - 1; i < k; i++)
	{
		// �������� "������" �������� �������
		if (iData[i] < 0)
		{
			int x = iData[i];

			// ���� ���������� ������ ������-������ � ������������ ������ �������������� iData[i] �� ������������� iData[k]
			for (k; k > i; k--)
			{
				if (iData[k] < 0)
				{
					iData[i] = iData[k];
					iData[k] = x;
					k--;
					break;
				}
			}
		}
	}
}
void ReverseNegItemsInSitu2(int*& iData, int iLen)
// ��������� �������� ������ ��� ������������� ��������� �������.
{
	for (int i = 0, j = iLen - 1; i < j; i++, j--) {
		while (iData[i] > 0 && i < iLen) i++;
		while (iData[j] > 0 && j >= 0) j--;
		int iTemp = iData[i];
		iData[i] = iData[j];
		iData[j] = iTemp;
	}
}
void Task1_3_7()
{
	int* iData = global_iDataArray_1_3;
	int iLen = global_iDataArray_Len_1_3;

	ReverseNegItemsInSitu(iData, iLen);

	cout << "\nTask1_3_7.\n";

	cout << "iData:" << "\n";
	for (int i = 0; i < iLen; i++)
	{
		cout << "[" << i << "] = " << global_iDataArray_1_3[i] << "\n";
	}
}

// ������� 8. ��������� ������ ���������� ������� int � ��������� [iMinVal, iMaxVal].
int* CreateRandIntArr(int iLen, int iMinVal, int iMaxVal)
{
	int* Array = new int[iLen] {};

	for (int i = 0; i < iLen; i++)
	{
		Array[i] = GetRandomNumberInt(iMinVal, iMaxVal);
	}

	return Array;
}
void Task1_3_8()
{
	int iLen = 0;

	int iMinVal = 0;
	int iMaxVal = 0;

	cout << "\nTask1_3_8.\n";

	cout << "iLen = ";
	cin >> iLen;

	cout << "iMinVal = ";
	cin >> iMinVal;

	cout << "iMaxVal = ";
	cin >> iMaxVal;

	int* Array = CreateRandIntArr(iLen, iMinVal, iMaxVal);

	cout << "Array:\n";
	for (int i = 0; i < iLen; i++)
	{
		cout << "[" << i << "] = " << Array[i] << "\n";
	}

	delete[] Array;
}

// ������� 9. ��������� ������ �� iLen ��������� ���������� ������� float � ��������� [rMinVal, rMaxVal].
float* CreateRandFloatArr(int iLen, float rMinVal, float rMaxVal)
{
	float* Array = new float[iLen] {};

	for (int i = 0; i < iLen; i++)
	{
		Array[i] = GetRandomNumberFloat(rMinVal, rMaxVal);
	}

	return Array;
}
void Task1_3_9()
{
	int iLen = 0;

	float rMinVal = 0;
	float rMaxVal = 0;

	cout << "\nTask1_3_9.\n";

	cout << "iLen = ";
	cin >> iLen;

	cout << "iMinVal = ";
	cin >> rMinVal;

	cout << "iMaxVal = ";
	cin >> rMaxVal;

	float* Array = CreateRandFloatArr(iLen, rMinVal, rMaxVal);

	cout << "Array:\n";
	for (int i = 0; i < iLen; i++)
	{
		cout << "[" << i << "] = " << Array[i] << "\n";
	}

	delete[] Array;
}

// ������� 10. �������� � ������ ������ ��� �����, � ������� ������ � ����� ����� (����� ��������) - ����.
int* SelectTensZero(int* iData, int iLen, int& iSize)
{
	// ������� ����� iSize ��� ������ �������.
	for (int i = 0; i < iLen; i++)
	{
		// ���������, ��� ������� ����� ����.
		if (iData[i] >= 100 && (iData[i] / 10) % 10 == 0) iSize++;
	}

	int* Array = new int[iSize] {};

	// ��������� ����� ������.
	for (int i = 0, j = 0; j < iSize; i++)
	{
		// ���������, ��� ������� ����� ����.
		if (iData[i] >= 100 && (iData[i] / 10) % 10 == 0)
		{
			Array[j] = iData[i];
			j++;
		}
	}

	return Array;
}
int* SelectTensZero2(int* iData, int iLen, int& iOutCount)
// �������� � ������ ������ ��� �����, � ������� ������ � ����� ����� (����� ��������) - ����.
{
	iOutCount = 0;
	int* iDataOut = new int[iLen] {0};
	for (int i = 0; i < iLen - 1; i++) {
		int iVal = iData[i] / 10;
		if (!iVal) continue;// ���������� ����� < 10
		// ���� � ������� �������� ����� ����, ��������� ����� � �������� ������:
		if ((iVal / 10) * 10 == iVal) iDataOut[iOutCount++] = iData[i];
	}
	return iDataOut;
}
void Task1_3_10()
{
	int iLen = 0;

	int iSize = 0;

	int iMinVal = 0;
	int iMaxVal = 0;

	cout << "\nTask1_3_10.\n";

	cout << "iLen = ";
	cin >> iLen;

	cout << "iMinVal = ";
	cin >> iMinVal;

	cout << "iMaxVal = ";
	cin >> iMaxVal;

	int* Array1 = CreateRandIntArr(iLen, iMinVal, iMaxVal);

	int* Array2 = SelectTensZero(Array1, iLen, iSize);

	cout << "Array1:\n";
	for (int i = 0; i < iLen; i++)
	{
		cout << "[" << i << "] = " << Array1[i] << "\n";
	}

	cout << "Array2:\n";
	for (int i = 0; i < iSize; i++)
	{
		cout << "[" << i << "] = " << Array2[i] << "\n";
	}

	delete[] Array1;
	delete[] Array2;
}

// ������� 11. �������� �������� ������� ����� �� 1 ������, ������ ������� ���������� �� ����� ����������(����������� ����� �����).
void ArrCyclicShiftLeft(int*& iData, int iLen)
{
	int iFirst = iData[0];

	for (int i = 0; i < iLen - 1; i++) iData[i] = iData[i + 1];

	iData[iLen - 1] = iFirst;
}
void Task1_3_11()
{
	int* iData = global_iDataArray_1_3;
	int iLen = global_iDataArray_Len_1_3;

	ArrCyclicShiftLeft(iData, iLen);

	cout << "Task1_3_11.\n";
	cout << "iData:" << "\n";
	for (int i = 0; i < iLen; i++)
	{
		cout << "[" << i << "] = " << iData[i] << "\n";
	}
}

// ������� 12. �������� �������� ������� ������ �� 1 ������, ��������� ������� ���������� �� ����� ������� (����������� ����� ������).
void ArrCyclicShiftRight(int*& iData, int iLen)
{
	int iLast = iData[iLen - 1];

	for (int i = iLen - 1; i > 0; i--) iData[i] = iData[i - 1];

	iData[0] = iLast;
}
void Task1_3_12()
{
	int* iData = global_iDataArray_1_3;
	int iLen = global_iDataArray_Len_1_3;

	ArrCyclicShiftRight(iData, iLen);

	cout << "Task1_3_12.\n";
	cout << "iData:" << "\n";
	for (int i = 0; i < iLen; i++)
	{
		cout << "[" << i << "] = " << iData[i] << "\n";
	}
}