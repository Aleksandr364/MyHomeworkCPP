#include "DynArray.h"
#include <Windows.h>
#include <iostream>
#include "MyExceptions_for_DynArray.h"
#include <fstream>

std::string stringExceptionType_for_DynArray[] = {
	"\nnull_errors\n",
	"\nincArray_failed:\nincArray() = false:\ndata = nullptr or step = 0\n",
	"\nempty:\ncurrent_size = 0\n",
	"\nindex_too_large:\nindex >= current_size\n",
	"\nnull_data:\ndata = nullptr\n",
	"\ndynarray_doesnt_exist:\n data = nullptr\n",
	"\nmax_size_null\n",
	"\nstep_null\n"
};

void Test_DynArray()
{
	try
	{
		DynArray<int> New_iData_Dyn(10, 5);
		for (int i = 1; i <= 15; i++)
			New_iData_Dyn.PushBack(i);

		//New_iData_Dyn.Get(15);

		New_iData_Dyn.Show();
		std::cout << "Last Item = " << New_iData_Dyn.PopBack() << "\n";
		std::cout << "Last Item = " << New_iData_Dyn.PopBack() << "\n";
		New_iData_Dyn.Show();

		New_iData_Dyn.Insert(2, 100);

		New_iData_Dyn.Delete(2);

		New_iData_Dyn.Delete(New_iData_Dyn.Size() - 1);

		DynArray<int> Another_iData_Dyn(New_iData_Dyn);

		DynArray<int> Another_iData_Dyn2, Another_iData_Dyn3;
		Another_iData_Dyn2 = Another_iData_Dyn3 = New_iData_Dyn;

		DynArray<int> Another_iData_Dyn4(std::move(Another_iData_Dyn2));
		DynArray<int> Another_iData_Dyn5;
		Another_iData_Dyn5 = std::move(Another_iData_Dyn3);

		DynArray<int> Another_iData_Dyn6;
		Another_iData_Dyn6 = Another_iData_Dyn5 + Another_iData_Dyn4;

		std::cout << Another_iData_Dyn6 << Another_iData_Dyn5 << Another_iData_Dyn4;

		std::ofstream OutFile("OutFile.txt");
		OutFile << Another_iData_Dyn6 << Another_iData_Dyn5 << Another_iData_Dyn4;
		OutFile.close();

		DynArray<int> Input_iData_Dyn7, Input_iData_Dyn8, Input_iData_Dyn9;
		std::ifstream InFile("OutFile.txt");
		InFile >> Input_iData_Dyn7 >> Input_iData_Dyn8 >> Input_iData_Dyn9;
		InFile.close();
		std::cout << std::boolalpha << (Another_iData_Dyn6 == Input_iData_Dyn7) << std::noboolalpha << "\n";
		std::cout << std::boolalpha << (Another_iData_Dyn5 == Input_iData_Dyn8) << std::noboolalpha << "\n";
		std::cout << std::boolalpha << (Another_iData_Dyn4 == Input_iData_Dyn9) << std::noboolalpha << "\n";
		
		std::cout << Input_iData_Dyn7[10] << "\n";

		DynArray<DynArray<int>> dynArray2D;
		dynArray2D.PushBack(Another_iData_Dyn);
		dynArray2D.PushBack(Another_iData_Dyn2);
		dynArray2D.Show();
	}

	catch (MyExceptions_for_DynArray& error)
	{
		std::cout << "\n!!!MyExceptions_for_DynArray!!!\n";
		std::cout << error.What() << "\n";
	}
}