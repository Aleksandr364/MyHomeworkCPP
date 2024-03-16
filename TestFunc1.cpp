#include <iostream>

extern int iGlobal; // extern - ключевое слово указывает на внешнюю (в другом .cpp файле) глобальную переменную.
//extern int iGlobalStatic;

void TestFuncCout()
{
	std::cout << "iGlobal = " << iGlobal << "\n";
	//std::cout << "iGlobalStatic = " << iGlobalStatic << "\n";
}

void TestFunc_1()
{
	int iVal_1 = 1;

	// Статическая локальная переменная. Видна только в данной функции, но существует, пока существует программа.
	static int iVal_2 = 1;

	std::cout << "iVal_1 = " << iVal_1++ << "\n";
	std::cout << "iVal_2 = " << iVal_2++ << "\n";

}

void TestFunc_2()
{
	int iArray[5]{ 1, 2, 3, 4, 5 };

	int* iData = iArray;


	int iVal1 = *iData++;
	// int iVal1 = *iData;
	// iData++;


	int iVal2 = *(iData++);
	// int iVal2 = *iData;
	// iData++;


	int iVal3 = (*iData)++;
	// int iVal3 = *iData;
	// (*iData)++;


	int iVal4 = ++*iData;
	// (*iData)++;
	// int iVal4 = *iData;


	int iVal5 = *++iData;
	// ++iData;
	// iVal5 = *iData;
}

void TestCrash(int i)
{
	int iData[100]{};

	for (;;)
	{
		std::cout << i++ << "\n";
		TestCrash(i);
	}
}