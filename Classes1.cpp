#pragma once

#include "Classes1.h"

Phone_Book_Item::Phone_Book_Item()
{
	std::cout << "default constructor\n";
}

Phone_Book_Item* classes()
{
	// создание экземпляра (объекта) класса Phone_Book_Item
	// слева - класс Phone_Book_Item, справа - имя нового объекта phone_book

	// вызывается конструктор "по умолчанию"
	Phone_Book_Item phone_book_1;

	if (phone_book_1.Check_Phone_Number()) std::cout << "true\n";
	else std::cout << "false\n";

	phone_book_1.numberLen = 123;
	phone_book_1.Get_Phone_Number();

	// заголовок параметрического конструктора: Phone_Book_Item(std::string First_Name, std::string Surname, const char* Phone_Number, int Year_of_Birthday)
	// вызывается параметрический конструктор
	// создаётся стэковый объект (локальная память функции) 
	Phone_Book_Item phone_book_2("name", "second_name", "1234567890");

	if (phone_book_2.Check_Phone_Number()) std::cout << "true\n";
	else std::cout << "false\n";

	phone_book_2.Get_Phone_Number();

	// создаётся объект в куче
	Phone_Book_Item* phone_book_3 = new Phone_Book_Item("name*", "second_name*", "1234567890*");

	if (phone_book_3->Check_Phone_Number()) std::cout << "true\n";
	else std::cout << "false\n";

	phone_book_3->Get_Phone_Number();

	return phone_book_3;
}

int Classes_Func()
{
	Phone_Book_Item* Class_Phone_Book = classes();

	delete Class_Phone_Book;

	return 1;
}