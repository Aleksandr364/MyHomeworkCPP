#pragma once

#include <string>
#include <iostream>

class Phone_Book_Item {
// недоступен никому
private:
// доступен только "наследникам"
protected:
	std::string Name;
	std::string Surname;
	char* Phone_Number = nullptr;
	int Year_of_Birthday = 0;

	void Copy_Phone_Number(char* Phone_Number)
	{
		if (!Phone_Number) return;

		Free_Phone_Number();

		numberLen = (int)strlen(Phone_Number);	// вычисление длины Phone_Number
		Phone_Book_Item::Phone_Number = new char[numberLen + 1] {};	// выделение динамической памяти для char* Phone_Number ("numberLen + 1" - выделяется на +1 байт больше под "нультерминатор" ASCIIZ - гарантирует последний байт = ноль !ТАК НАДО!)
		memcpy(Phone_Book_Item::Phone_Number, Phone_Number, numberLen);
	}
	void Free_Phone_Number()
	{
		if (!Phone_Number) return;

		delete[] Phone_Number;
		Phone_Number = nullptr;
	}
	void moveFrom(Phone_Book_Item&& From) noexcept
	{
		numberLen = From.numberLen; From.numberLen = 0;
		Name = std::move(From.Name); // конструктор переноса std::move() для классов (объектов с конструкторами)
		Surname = From.Surname; From.Surname = "";
		Year_of_Birthday = From.Year_of_Birthday; From.Year_of_Birthday = 0;
		Phone_Number = From.Phone_Number; From.Phone_Number = nullptr;
	}
	void copyFrom(Phone_Book_Item& rhs)
	{
		numberLen = rhs.numberLen;
		Name = rhs.Name;
		Surname = rhs.Surname;
		Year_of_Birthday = rhs.Year_of_Birthday;
		Copy_Phone_Number(rhs.Phone_Number);
	}
// доступен всем
public:
	int numberLen = 0;
	// конструктор (constructor) - специальная функция, которая вызывается, когда класс создаётся
	// конструктор без параметров - "конструктор по умолчанию" (дефолтным) default constructor существует даже если его не задали (один)
	/*Phone_Book_Item()
	{
		std::cout << "default constructor\n";
	}*/
	Phone_Book_Item();
	// конструктор с одним параметром типа int (имя параметра можно не указывать)
	// конструктор с параметрами - параметрический parametric constructor (может быть сколько угодно)
	Phone_Book_Item(std::string First_Name, std::string Surname, const char* Phone_Number, int Year_of_Birthday = 1980):
		// список инициализации (присваиваем значения полям класса) здесь Name и Year_of_Birthday - поля класса, а значения в скобках - это локальные переменные (формальные параметры)
		Name(First_Name), Year_of_Birthday(Year_of_Birthday)
	{
		std::cout << "parametric constructor\n";

		Phone_Book_Item::Surname = Surname;
		
		Copy_Phone_Number((char*)Phone_Number);
	}
	// конструктор копирования обычный по синтаксису
	Phone_Book_Item(Phone_Book_Item& From)
	{
		copyFrom(From);
	}
	// конструктор копирования с дополнительными параметрами (int)
	Phone_Book_Item(Phone_Book_Item& From, int x)
	{
		copyFrom(From);
	}
	// константный конструктор копирования
	Phone_Book_Item(const Phone_Book_Item& From)
	{
		copyFrom((Phone_Book_Item&)From);
	}
	// overloaded "перегруженный" (переопределённый) оператор копирования-присваивания (copy assignment operator)
	Phone_Book_Item& operator=(Phone_Book_Item& rhs)
	{
		// this - указатель (адрес) на данный конкретный объект (стандартное ключевое слово) !всегда не нулевой!
		// ссылка - НЕ указатель, но тоже адрес
		// Phone_Book_Item& - ссылка, &rhs - адрес объекта (указатель)
		if (&rhs == this) return *this; // *this - переход от указателя (&rhs) к объекту - в данном случае ссылке (Phone_Book_Item&)

		copyFrom(rhs);

		return *this;
	}
	// overloaded"перегруженный" (переопределённый) оператор присваивания (copy assignment operator) для int
	Phone_Book_Item& operator=(int rhs)
	{
		Year_of_Birthday = rhs;

		return *this;
	}
	// overloaded "перегруженный" (переопределённый) оператор перемещения-присваивания (move assignment operator)
	Phone_Book_Item& operator=(Phone_Book_Item&& From) noexcept
	{
		if (&From == this) return *this; // *this - переход от указателя (&rhs) к объекту - в данном случае ссылке (Phone_Book_Item&)

		moveFrom((Phone_Book_Item&&)From);

		return *this;
	}
	// конструктор переноса "&&" (логика правоассоциативной ссылки rvalue)
	// noexcept - ключевое слово, которое гарантирует, что в функции(методе) не будет исключений(аварийных ситуаций)
	Phone_Book_Item(Phone_Book_Item&& From) noexcept
	{
		moveFrom((Phone_Book_Item&&)From);
	}
	// деструктор (destructor) - специальная функция, которая вызывается, когда класс уничтожается (ОН ВСЕГДА ОДИН)
	~Phone_Book_Item()
	{
		std::cout << "destructor\n";

		Free_Phone_Number();
	}
	// функция в классе - "метод"
	// конструкторы и деструктор - "специальный метод"
	// данные - "поля"
	bool Check_Phone_Number()
	{
		if (!Phone_Number) return false;

		return true;
	}
	// "Геттер" - прочитать значение поля, чтобы не обращаться к нему напрямую (protected, private)
	char* Get_Phone_Number()
	{
		std::cout << numberLen;
		return Phone_Number;
	}
	std::string Get_Name()
	{
		return Name;
	}
	// "Сеттер" - установить значение поля, чтобы не делать этого напрямую
	void Set_Phone_Number(const char* Phone_Number)
	{
		Copy_Phone_Number((char*)Phone_Number);
	}
	// Любой метод Класса может работать с любым Полем этого же класса
	
	Phone_Book_Item Test(Phone_Book_Item rhs)
	{
		rhs.Name = "dfgdgadgag";

		return rhs;
	}
};
