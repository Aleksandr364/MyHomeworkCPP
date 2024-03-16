#pragma once

#include <string>
#include <iostream>

class Phone_Book_Item {
// ���������� ������
private:
// �������� ������ "�����������"
protected:
	std::string Name;
	std::string Surname;
	char* Phone_Number = nullptr;
	int Year_of_Birthday = 0;

	void Copy_Phone_Number(char* Phone_Number)
	{
		if (!Phone_Number) return;

		Free_Phone_Number();

		numberLen = (int)strlen(Phone_Number);	// ���������� ����� Phone_Number
		Phone_Book_Item::Phone_Number = new char[numberLen + 1] {};	// ��������� ������������ ������ ��� char* Phone_Number ("numberLen + 1" - ���������� �� +1 ���� ������ ��� "��������������" ASCIIZ - ����������� ��������� ���� = ���� !��� ����!)
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
		Name = std::move(From.Name); // ����������� �������� std::move() ��� ������� (�������� � ��������������)
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
// �������� ����
public:
	int numberLen = 0;
	// ����������� (constructor) - ����������� �������, ������� ����������, ����� ����� ��������
	// ����������� ��� ���������� - "����������� �� ���������" (���������) default constructor ���������� ���� ���� ��� �� ������ (����)
	/*Phone_Book_Item()
	{
		std::cout << "default constructor\n";
	}*/
	Phone_Book_Item();
	// ����������� � ����� ���������� ���� int (��� ��������� ����� �� ���������)
	// ����������� � ����������� - ��������������� parametric constructor (����� ���� ������� ������)
	Phone_Book_Item(std::string First_Name, std::string Surname, const char* Phone_Number, int Year_of_Birthday = 1980):
		// ������ ������������� (����������� �������� ����� ������) ����� Name � Year_of_Birthday - ���� ������, � �������� � ������� - ��� ��������� ���������� (���������� ���������)
		Name(First_Name), Year_of_Birthday(Year_of_Birthday)
	{
		std::cout << "parametric constructor\n";

		Phone_Book_Item::Surname = Surname;
		
		Copy_Phone_Number((char*)Phone_Number);
	}
	// ����������� ����������� ������� �� ����������
	Phone_Book_Item(Phone_Book_Item& From)
	{
		copyFrom(From);
	}
	// ����������� ����������� � ��������������� ����������� (int)
	Phone_Book_Item(Phone_Book_Item& From, int x)
	{
		copyFrom(From);
	}
	// ����������� ����������� �����������
	Phone_Book_Item(const Phone_Book_Item& From)
	{
		copyFrom((Phone_Book_Item&)From);
	}
	// overloaded "�������������" (���������������) �������� �����������-������������ (copy assignment operator)
	Phone_Book_Item& operator=(Phone_Book_Item& rhs)
	{
		// this - ��������� (�����) �� ������ ���������� ������ (����������� �������� �����) !������ �� �������!
		// ������ - �� ���������, �� ���� �����
		// Phone_Book_Item& - ������, &rhs - ����� ������� (���������)
		if (&rhs == this) return *this; // *this - ������� �� ��������� (&rhs) � ������� - � ������ ������ ������ (Phone_Book_Item&)

		copyFrom(rhs);

		return *this;
	}
	// overloaded"�������������" (���������������) �������� ������������ (copy assignment operator) ��� int
	Phone_Book_Item& operator=(int rhs)
	{
		Year_of_Birthday = rhs;

		return *this;
	}
	// overloaded "�������������" (���������������) �������� �����������-������������ (move assignment operator)
	Phone_Book_Item& operator=(Phone_Book_Item&& From) noexcept
	{
		if (&From == this) return *this; // *this - ������� �� ��������� (&rhs) � ������� - � ������ ������ ������ (Phone_Book_Item&)

		moveFrom((Phone_Book_Item&&)From);

		return *this;
	}
	// ����������� �������� "&&" (������ ������������������ ������ rvalue)
	// noexcept - �������� �����, ������� �����������, ��� � �������(������) �� ����� ����������(��������� ��������)
	Phone_Book_Item(Phone_Book_Item&& From) noexcept
	{
		moveFrom((Phone_Book_Item&&)From);
	}
	// ���������� (destructor) - ����������� �������, ������� ����������, ����� ����� ������������ (�� ������ ����)
	~Phone_Book_Item()
	{
		std::cout << "destructor\n";

		Free_Phone_Number();
	}
	// ������� � ������ - "�����"
	// ������������ � ���������� - "����������� �����"
	// ������ - "����"
	bool Check_Phone_Number()
	{
		if (!Phone_Number) return false;

		return true;
	}
	// "������" - ��������� �������� ����, ����� �� ���������� � ���� �������� (protected, private)
	char* Get_Phone_Number()
	{
		std::cout << numberLen;
		return Phone_Number;
	}
	std::string Get_Name()
	{
		return Name;
	}
	// "������" - ���������� �������� ����, ����� �� ������ ����� ��������
	void Set_Phone_Number(const char* Phone_Number)
	{
		Copy_Phone_Number((char*)Phone_Number);
	}
	// ����� ����� ������ ����� �������� � ����� ����� ����� �� ������
	
	Phone_Book_Item Test(Phone_Book_Item rhs)
	{
		rhs.Name = "dfgdgadgag";

		return rhs;
	}
};
