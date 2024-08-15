// RAII "Resource Acquisition Is Initialization"

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "RAII.h"

namespace RAII
{
	RAII_file_wrap_2::RAII_file_wrap_2(std::string FileName, std::string Mode) : FileName(FileName)
	{
		errno_t err = fopen_s(&file, FileName.c_str(), Mode.c_str());
		if (err || !file) throw 0;
	};

	RAII_file_wrap_2::~RAII_file_wrap_2()
	{
		if (file) fclose(file);
	};

	size_t RAII_file_wrap_2::Write(const void* buffer, size_t buffLen)
	{
		return fwrite(buffer, 1, buffLen, file);
	};

	size_t RAII_file_wrap_2::Read(void* buffer, size_t buffLen)
	{
		return fread(buffer, 1, buffLen, file);
	};

	std::string RAII_file_wrap_2::Get_FileName()
	{
		return FileName;
	};

	void TestRAII()
	{
		TestStruct* Struct = new TestStruct();
		RAII_memory_wrap<TestStruct> Memory_wrap;
	};

	void TestRAII_file()
	{
		RAII_file_wrap New_file;
	};

	void TestRAII_file_2()
	{
		RAII_file_wrap_2 New_file_2("Test_Class_File_2.txt", "a+");
		New_file_2.Write("Hello!", strlen("Hello!"));
	};

};