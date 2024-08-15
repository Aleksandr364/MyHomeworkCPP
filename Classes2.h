#pragma once

#include <iostream>

class Limb
{
	int index = 0;

public:

	// ��������� ����������� ������ Limb
	Limb() {}

	// ��������������� ����������� ������ Limb
	Limb(int index)
	{
		Limb::index = index;
	}

	Limb(int, int)
	{

	}
};

class Tail
{

};

// ������� ���������
// const int LimbCount = 4;
// ��������� ������������� (�� ������ ������ 12 ������)
#define LIMBCOUNT 4

// ����������� ����� (���� �� ���� ����������� �������)
class AbstractClass
{
public:

	int x = 1;

	AbstractClass()
	{

	}

	// ������ ����������� ���������� � "�����" ��� ����, ����� ������-���������� ���� ������������ (������ ���� ����� ���� �����������).
	virtual ~AbstractClass() = 0
	{

	}

	// ����������� �������
	virtual void Test()
	{

	}

	virtual int GetVal()
	{
		std::cout << "AbstractClass x = "<< x << "\n";
		return x;
	}

	// ������ ����������� ������� (pure virtual function) - � ������� ��� ����. ����� ������� ��� "����������� �����".
	virtual int GetVal2() = 0;
};

// ����� ������������
class Monkey
{
private:

protected:

	int x = 0;

	int brainVolume = 0;

	// ������� ����������
	// 4 ������� �������� (����������� �� ����������)
	Limb* Array[LIMBCOUNT]{};

	// ��� ������ ���������������� ������������ Limb, ����� ��� ������ ���������� ������������ Limb
	// ����� ��� ���������� ������
	Limb Array2[LIMBCOUNT]{ { 1, 2 }, { 3, 4 } };

	Tail tail;

public:

	// ��������� �����������
	Monkey()
	{
		for (int i = 0; i < LIMBCOUNT; i++)
			// Array[i] = new Limb;
			// Array[i] = new Limb(); // ���������� ��������� ����������� ����� Limb  � ������ ����� ������ ��������� "� ����" � ������� � Array[i]
			Array[i] = new Limb(i+1); // ���������� ��������������� ����������� ������ Limb

		std::cout << "Constructor Monkey\n";
	}

	~Monkey()
	{
		for (int i = 0; i < LIMBCOUNT; i++)
		{
			delete Array[i];
			Array[i] = nullptr;
		}

		std::cout << "Destructor ~Monkey\n";
	}

	void Step(float az, int speed)
	{

	}

	void TailMove(int speed)
	{

	}
};


class Intermediate : public Monkey
{
private:

	Tail tail;

	void TailMove(int speed)
	{

	}

protected:

public:

	Intermediate()
	{
		std::cout << "Constructor Intermediate\n";
	}

	~Intermediate()
	{
		std::cout << "Destructor ~Intermediate\n";
	}
};

// ����� ��������� (�������� �����)
class Homosapiens : public Intermediate
{
private:



protected:

	std::string Name;

public:

	Homosapiens()
	{
		std::cout << "Constructor Homosapiens\n";
		std::cout << x << "\n";
	}

	~Homosapiens()
	{
		std::cout << "Destructor ~Homosapiens\n";
	}
};

// ���������-��������� ������ AbstractClass
struct Structure1: public AbstractClass
{
private:

protected:

public:

	int x = 2;

	int GetVal()
	{
		std::cout << "Structure1 x = " << x << "\n";
		return x;
	}

	int GetVal2()
	{
		return 0;
	}
};

class FromStruct1 : public Structure1
{
private:

protected:

public:

	int x = 3;

	int GetVal()
	{
		std::cout << "FromStruct1 x = " << x << "\n";
		return x;
	}
};

class BaseBase
{

};

// ����������� ������������.
class BaseClass1: virtual public BaseBase
{
private:

protected:

public:

	int x = 0;

	void Test()
	{

	}
};

// ����������� ������������.
class BaseClass2: virtual public BaseBase
{
private:

protected:

public:

	int y = 1;

	void Test()
	{

	}
};

// ������������� ������������.
class NextClass : public BaseClass1, public BaseClass2
{

};

class ShowNoExplicit
{
public:

	ShowNoExplicit() {}

	ShowNoExplicit(int x) {}

	ShowNoExplicit(int x, int y) {}

	operator bool() { return true; }
};

class ShowWithExplicit
{
public:

	explicit ShowWithExplicit() {}

	explicit ShowWithExplicit(int x) {}

	explicit ShowWithExplicit(int x, int y) {}

	explicit operator bool() { return true; }
};