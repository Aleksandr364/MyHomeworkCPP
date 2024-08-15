#include <Windows.h>
#include <iostream>
#include "Exceptions.h"
#include <cstring>

int invalidDivision(int x, int y)
{
	return x / y;
}

void invalidMemoryAccess()
{
	int* x = nullptr;
	*x = 10;
}

void GenerateException(int x)
{
	if (x > 100) throw 0; // throw - оператор для генерации исключения "выбросить исключение"
	std::cout << "\nFunc\n";
}


void TestException()
{
	// GenerateException(101); // незащищенный код, приводит к аварийному завершению программы
	
	// try{} - защищенный код (который будет искать обработчик исключений)
	try
	{
		GenerateException(0);
		GenerateException(101);
	}

	// catch (...) - фильтр обработки исключений (если ... - значит всех)
	catch (...)
	{
		std::cout << "\nException!";
	}
	std::cout << "\n" << "Finish\n";
}

std::string stringExceptionType[] = { "null", "filenotopen", "invalideversion" };

void GenerateMyNewExceptions()
{
	throw std::invalid_argument("invalid_argument");
}

TestStruct2* GlobalTestStruct = nullptr;

void GenerateMyExceptions()
{
	TestStruct2 NewTestStruct("text");
	TestStruct2 NewTestStruct3 = TestStruct2("text3");
	GlobalTestStruct = new TestStruct2("text_new");
	throw MyExceptions(ExceptionType::filenotopen);
}

void Exceptions()
{
	try
	{
		//GenerateMyExceptions();
		//GenerateMyNewExceptions();
		//GenerateException(101);
	}
	
	// если throw 0 (целое число)
	catch (int e)
	{
		std::cout << "error = " << e << "\n";
	}

	// если throw ExceptionType::filenotopen
	catch (ExceptionType e)
	{
		std::cout << "error = " << (int)e << "\n";
	}

	// если throw MyExceptions(ExceptionType::filenotopen)
	catch (MyExceptions &error)
	{
		std::cout << "\nMyException!\n";
		std::cout << error.What() << "\n";
		delete GlobalTestStruct;
		GlobalTestStruct = nullptr;
	}

	catch (std::invalid_argument& error)
	{
		std::cout << "\ninvalid_argument!\n";
		std::cout << error.what() << "\n";
	}

	catch (...)
	{
		std::cout << "\nUnknownException!";
	}
}

void TestSEH()
{
	__try
	{
		__try
		{
			invalidDivision(10, 1);
			invalidMemoryAccess();
		}

		// EXCEPTION_EXECUTE_HANDLER - обработчик исключения
		// EXCEPTION_CONTINUE_EXECUTION - установить возможность исправления ошибки
		// EXCEPTION_CONTINUE_SEARCH - продолжить искать обработчик выше по стеку
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			std::cout << "\nTestSEH __except\n";
		}
	}
	__finally
	{
		std::cout << "\nTestSEH __finally\n";
	}
}

void TestColor(ColorType Color)
{
	switch (Color)
	{
	case red: std::cout << "\nred\n"; break;
	case blue: std::cout << "\nblue\n"; break;
	case green: std::cout << "\ngreen\n"; break;
	case orange: std::cout << "\norange\n"; break;
	default: std::cout << "\nunknown\n";
	}
}


void TestColor(_ColorType Color)
{
	switch (Color)
	{
	case _ColorType::red: std::cout << "\nred\n"; break;
	case _ColorType::blue: std::cout << "\nblue\n"; break;
	case _ColorType::green: std::cout << "\ngreen\n"; break;
	case _ColorType::orange: std::cout << "\norange\n"; break;
	default: std::cout << "\nunknown\n";
	}
}