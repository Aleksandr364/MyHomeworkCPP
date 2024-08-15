#pragma once

enum class ExceptionType_for_DynArray { null_errors, incArray_failed, empty, index_too_large, null_data, dynarray_doesnt_exist, max_size_null, step_null };

std::string stringExceptionType_for_DynArray[];

struct MyExceptions_for_DynArray : public std::exception
{
	ExceptionType_for_DynArray Exception = ExceptionType_for_DynArray::null_errors;

	MyExceptions_for_DynArray(ExceptionType_for_DynArray Exception) : Exception(Exception) {};
	
	const char* What() const noexcept // noexcept() == noexcept(true) - вместо throw()
	{
		return stringExceptionType_for_DynArray[int(Exception)].c_str();
	}
};