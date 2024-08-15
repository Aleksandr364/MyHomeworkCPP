#pragma once

#include <iostream>

class Limb
{
	int index = 0;

public:

	// дефолтный конструктор класса Limb
	Limb() {}

	// параметрический конструктор класса Limb
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

// задание константы
// const int LimbCount = 4;
// директива препроцессора (по смыслу аналог 12 строки)
#define LIMBCOUNT 4

// полиморфный класс (хотя бы одна виртуальная функция)
class AbstractClass
{
public:

	int x = 1;

	AbstractClass()
	{

	}

	// Чистый виртуальный деструктор с "телом" для того, чтобы классы-наследники были абстрактными (делает свой класс тоже абстрактным).
	virtual ~AbstractClass() = 0
	{

	}

	// виртуальная функция
	virtual void Test()
	{

	}

	virtual int GetVal()
	{
		std::cout << "AbstractClass x = "<< x << "\n";
		return x;
	}

	// Чистая виртуальная функция (pure virtual function) - у функции нет тела. Можно назвать как "абстрактный метод".
	virtual int GetVal2() = 0;
};

// класс родительский
class Monkey
{
private:

protected:

	int x = 0;

	int brainVolume = 0;

	// паттерн композиции
	// 4 нулевых поинтера (конструктор не вызывается)
	Limb* Array[LIMBCOUNT]{};

	// два вызова параметрического конструктора Limb, потом два вызова дефолтного конструктора Limb
	// лучше для маленького класса
	Limb Array2[LIMBCOUNT]{ { 1, 2 }, { 3, 4 } };

	Tail tail;

public:

	// дефолтный конструктор
	Monkey()
	{
		for (int i = 0; i < LIMBCOUNT; i++)
			// Array[i] = new Limb;
			// Array[i] = new Limb(); // вызывается дефолтный конструктор класс Limb  и объект этого класса создается "в куче" и пишется в Array[i]
			Array[i] = new Limb(i+1); // вызывается параметрический конструктор класса Limb

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

// класс наследник (дочерний класс)
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

// структура-наследник класса AbstractClass
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

// Виртуальное наследование.
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

// Виртуальное наследование.
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

// Множественное наследование.
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