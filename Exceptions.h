#pragma once

void GenerateException(int x);
void TestException();


enum ColorType { red, blue, green, orange };

enum class _ColorType { red, blue, green, orange };

void TestColor(ColorType Color);

void TestColor(_ColorType Color);

enum class ExceptionType { null, filenotopen, invalideversion };

std::string stringExceptionType[];

// ��� ������������� ���������� ���������� ��������� ����� (stack unwinding), ����� ���������� ����� ������� ������� ���������.
// ���� � ������� ������� ����� ������ �� ������, �� ���������� ����� ���� ������������ ��������� �������� � ������� � ���������� �������.
struct MyExceptions: public std::exception
{
	ExceptionType Exception = ExceptionType::null;

	MyExceptions(ExceptionType Exception) : Exception(Exception) {};
	const char* What() const throw() { return stringExceptionType[int(Exception)].c_str(); }
};

void GenerateMyExceptions();

void Exceptions();

struct TestStruct2
{
	std::string text1;

	TestStruct2() = default;
	TestStruct2(std::string text) : text1(text) // ������ ������������� "...: text1(text)" = "...: text1 = text"
	{
		std::cout << "\nConstructor TestStruct2!" << text1 << "\n";
	}
	~TestStruct2()
	{
		std::cout << "\nDestructor TestStruct2!" << text1 << "\n";
	}
};

void TestSEH();