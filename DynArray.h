#pragma once

#include <cstring>
#include <iostream>
#include "MyExceptions_for_DynArray.h"

// ������������ ���������� ���� (�����)
// PushBack, PopBack - �������� ��������
template<typename T> class DynArray
{

protected:

	T* data = nullptr;

	// ������� ��������� ������������
	uint32_t current_size = 0;
	// ������� ��-�� ������������
	uint32_t max_size = 0;
	// ��� ���������� �������
	uint32_t step = 0;

	void Allocate()
	{
		data = new T[max_size]{};
	}

	bool incArray()
	{
		if (!data) return false;

		if (!step) return false;

		uint32_t new_max_size = max_size + step;

		T* new_data = new T[new_max_size]{};

		// sizeof(�) - ������ ���� "�" � ������
		memcpy(new_data, data, sizeof(T) * max_size);

		delete[] data;

		data = new_data;

		max_size = new_max_size;

		return true;
	}

	void CopyArray(const DynArray& rhs)
	{
		data = new T[rhs.max_size];
		memcpy(data, rhs.data, sizeof(T) * rhs.max_size);

		current_size = rhs.current_size;
		max_size = rhs.max_size;
		step = rhs.step;
	}

	void MoveArray(DynArray&& rhs) noexcept
	{
		data = rhs.data; rhs.data = nullptr;

		current_size = rhs.current_size; rhs.current_size = 0;
		max_size = rhs.max_size; rhs.max_size = 0;
		step = rhs.step; rhs.step = 0;
	}

	void DestructData()
	{
		delete[] data;
		data = nullptr;
		current_size = 0;
		max_size = 0;
		step = 0;
	}

public:

	DynArray() = default;

	DynArray(uint32_t max_size, uint32_t step): max_size(max_size), step(step)
	{
		Allocate();
		std::cout << "DynArray param. constructor.\n";
		std::cout << std::hex << std::showbase << this << std::noshowbase << std::dec << "\n";
	}

	DynArray(DynArray& rhs)
	{
		CopyArray(rhs);
		std::cout << "DynArray copy constructor.\n";
		std::cout << std::hex << std::showbase << this << std::noshowbase << std::dec << "\n";
	}

	DynArray(const DynArray& rhs)
	{
		CopyArray(rhs);
		std::cout << "DynArray const copy constructor.\n";
		std::cout << std::hex << std::showbase << this << std::noshowbase << std::dec << "\n";
	}

	DynArray(DynArray&& rhs) noexcept
	{
		// MoveArray((DynArray&&)rhs); <- ���������� ���� � ����� � "C style type cast"
		// MoveArray(static_cast<DynArray&&>(rhs)); // <- ���������� ���� � ����� C++ (���� �� ����������)
		MoveArray(std::move(rhs)); // <- ���������� ���� � ����� C++ (modern C++) � ������� std::move()
		std::cout << "DynArray move constructor.\n";
		std::cout << std::hex << std::showbase << this << std::noshowbase << std::dec << "\n";
	}

	DynArray& operator=(const DynArray& rhs)
	{
		if (&rhs == this) return *this;

		DestructData();

		CopyArray(rhs);

		std::cout << "DynArray copy-assign.\n";
		std::cout << std::hex << std::showbase << this << std::noshowbase << std::dec << "\n";

		return *this;
	}

	DynArray& operator=(DynArray&& rhs) noexcept
	{
		if (&rhs == this) return *this;

		DestructData();

		// MoveArray((DynArray&&)rhs); <- ���������� ���� � ����� � "C style type cast"
		// MoveArray(static_cast<DynArray&&>(rhs)); // <- ���������� ���� � ����� C++ (���� �� ����������)
		MoveArray(std::move(rhs)); // <- ���������� ���� � ����� C++ (modern C++) � ������� std::move()

		std::cout << "DynArray move-assign.\n";
		std::cout << std::hex << std::showbase << this << std::noshowbase << std::dec << "\n";

		return *this;
	}

	~DynArray()
	{
		DestructData();
		std::cout << "DynArray destructor.\n";
		std::cout << std::hex << std::showbase << this << std::noshowbase << std::dec << "\n";
	}

	bool Empty()
	{
		return !current_size;
	}
	uint32_t Size()
	{
		return current_size;
	}
	uint32_t MaxSize()
	{
		return max_size;
	}
	void SetStep(uint32_t new_step)
	{
		step = new_step;
	}
	uint32_t GetStep()
	{
		return step;
	}
	void Clear()
	{
		current_size = 0;
	}

	// �������� ����� ������� � ����� �������
	void PushBack(T value)
	{
		if (current_size >= max_size)
			if (!incArray()) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::incArray_failed);
		data[current_size++] = value;
	}

	// ������ �� ����� ������� � ��������� ������� �������������� ���������
	T PopBack()
	{
		if (!current_size) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::empty);
		T value = data[--current_size];
		return value;
	}

	T PopFront()
	{
		if (!current_size) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::empty);
		T value = data[0];
		Delete(0);
		return value;
	}

	void Set(uint32_t index, T value)
	{
		if (index >= current_size) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::index_too_large);
		data[index] = value;
	}

	T Get(uint32_t index)
	{
		if (index >= current_size) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::index_too_large);
		return data[index];
	}

	T operator[](uint32_t index) // ��� �������� ������������ �������
	{
		return data[index];
	}

	T at(uint32_t index) // at == operator[] � ��������� ������������ ������� (�������� ��������, ��� ��� ��������)
	{
		return Get(index);
	}

	T operator()(uint32_t index)
	{
		return Get(index);
	}

	T GetFirst()
	{
		if (!current_size) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::empty);

		return data[0];
	}

	T GetLast()
	{
		if (!current_size) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::empty);

		return data[current_size - 1];
	}

	// �������� ������� value � ������� index
	void Insert(uint32_t index, T value)
	{
		if (index >= current_size) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::index_too_large);

		if (current_size >= max_size)
			if (!incArray()) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::incArray_failed);

		memcpy(data + index + 1, data + index, sizeof(T) * (current_size - index));
		data[index] = value;
		current_size++;
	}

	void Delete(uint32_t index)
	{
		if (index >= current_size) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::index_too_large);

		// ��� ����, ����� ������� ��������� ������� ��������� "(current_size - index - 1)" - ������ ��� ���������� ������ �� ����
		memcpy(data + index, data + index + 1, sizeof(T) * (current_size - index - 1));
		current_size--;
	}


	bool operator==(const DynArray& rhs)
	{
		if (current_size != rhs.current_size) return false;

		if (!data || !rhs.data) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::null_data);

		for (uint32_t i = 0; i < current_size; i++)
			if (data[i] != rhs.data[i]) return false;
		return true;
	}

	bool operator!=(const DynArray& rhs)
	{
		return !operator==(rhs);
	}

	DynArray operator+(const DynArray& rhs)
	{
		int new_max_size = (max_size >= rhs.max_size) ? max_size + rhs.current_size : rhs.max_size + current_size; // ��������� �������� (����������) ��� if

		DynArray New_DynArray(new_max_size, std::max(step, rhs.step));

		memcpy(New_DynArray.data, data, sizeof(T) * current_size);
		memcpy(New_DynArray.data + current_size, rhs.data, sizeof(T) * rhs.current_size);
		New_DynArray.current_size = current_size + rhs.current_size;

		return New_DynArray; // ���������� ������ ����� std::move(), � �� �����������!!!
	}

	DynArray operator+=(const DynArray& rhs)
	{	
		// � �������� ������� (������� ��� ����������) ��������� ������ ��� ������������ ������ (rhs)
		if (!data) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::dynarray_doesnt_exist);
		if (!max_size) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::max_size_null);
		if (!step) throw MyExceptions_for_DynArray(ExceptionType_for_DynArray::step_null);

		max_size += rhs.current_size;
		current_size += rhs.current_size;

		memcpy(data + current_size, rhs.data, sizeof(T) * rhs.current_size);

		return *this;
	}

	// "friend" - ��������� ������ � ����� ���������� ����� � ������� ������ (friend - ��� �� ����� ������, � ������� ����� �������������)
	// �������� "<<" ����� ������ ����� ��������� ���������� ������� - ������ ������� �������� "<<" ������� ������, �� ������ ���� ����������
	// �� � ������ ������ ���������� ���������� �������� "<<" ������ ������ - ��� ���������� "HIDDEN FRIEND"
	friend std::ostream& operator<<(std::ostream& output, const DynArray<T>& rhs)
	{
		output << rhs.current_size << "\n";
		output << rhs.max_size << "\n";
		output << rhs.step << "\n";

		for (uint32_t i = 0; i < rhs.current_size; i++)
			output << rhs.data[i] << "\n";

		return output;
	}

	friend std::istream& operator>>(std::istream& input, DynArray<T>& rhs)
	{
		rhs.DestructData();
		input >> rhs.current_size;
		input >> rhs.max_size;
		input >> rhs.step;
		rhs.Allocate();

		for (uint32_t i = 0; i < rhs.current_size; i++)
			input >> rhs.data[i];

		return input;
	}

	void Show(std::ostream& out = std::cout)
	{
		out << "Show:\n";
		out << "current_size = " << current_size << "\n";
		out << "max_size = " << max_size << "\n";
		out << "step = " << step << "\n";

		for (uint32_t i = 0; i < current_size; i++)
			out << i << ": " << data[i] << "\n";
	}
};

// ���������� ������� �������������� ��������� "+", ������������ 2 ������������ ������� �� ����
// template<typename T> DynArray<T> operator+(DynArray<T>& lhs, DynArray<T>& rhs) {}

void Test_DynArray();