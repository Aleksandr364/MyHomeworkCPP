#define _CRT_SECURE_NO_WARNINGS

#include "Classes1.h"
#include "Task1.h"
#include "Classes2.h"
#include "ClassesTask1.h"
#include "Global.h"
#include "NewFileH.h"
#include "Exceptions.h"
#include "RAII.h"
#include "DynArray.h"
#include "HashTable.h"

using namespace RAII;

int Array_1[10]; // ���������� ������ - ���������� ������

void Func_1()
{
	// int Array[] == int*Array
	int Array_2[10]{ 0 }; // ��������� (��������) ������ - �������������� ������
	int* Array_3 = new int[10] {0}; // heap == ������������ ������ == ����
}

int* Func_2(int iLen)
{
	int* Array = new int[iLen] {0};

	for (int i = 0; i < iLen; i++) Array[i] = i + 1;

	return Array;
}

// ����������� ���������� ����������.
static int iGlobalStatic = 10;

// ���������� ���������.
int iGlobal = 11;

// ��� ������� ������������ ���� � ������� ��������� �������� ��������:
int TestClass_2::count;


// ������
int Classes_Func();

Phone_Book_Item TestMoveConstructor()
{
	Phone_Book_Item phone_book("Vasya", "Ffgdg", "353665");

	return phone_book;
}

// ������� ������ ���������� ��� ���������� ��������.
void Swap(int& x, int& y)
{
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
}

// zero rule - ������� ���� (�� ����� ������������ �����������: ��� �������� �������������)
struct Example
{
	int x = 0;
	float y = 0;
	std::string text;

	Example() = default;

	Example(int x, float y, std::string text): x(x), y(y), text(text) {}
};


void TestExplicit()
{
	ShowNoExplicit object1 = 10;
	bool val1 = object1;
	ShowWithExplicit object2({(int)10.1});
	bool val2 = (bool)object2;
};

uint32_t HashFunc(const char* text);

// trailing type - ��������� ���
auto main() -> int

//int main()
{
	std::cout << HashFunc("Hello!");
	std::cout << HashFunc("Hello!2");
	std::cout << HashFunc("chardff text");

	HashTable hashTableObj;
	hashTableObj.add("Hello!");
	hashTableObj.add("Hello!2");
	hashTableObj.add("chardff text");

	TestExplicit();

	TestArray2D();

	Test_DynArray();

	return 0;

	//	// ������� ������� phone_book_1 ������ Phone_Book_Item � ������� std::move()
	//	// Phone_Book_Item phone_book_1 = std::move(TestMoveConstructor());

	//	Phone_Book_Item phone_book_1("Vasya", "Ffgdg", "353665");

	//	Phone_Book_Item phone_book_2 = phone_book_1; 

	//	Phone_Book_Item phone_book_3;
	//	phone_book_3 = Phone_Book_Item("A111", "B222", "999999");

	//	phone_book_3 = 25;

	//	//Classes_Func();

	//	Phone_Book_Item phone_book_100("Sasha", "Antipin", "23742947242098");

	//	// std::cout << phone_book_100.Get_Name();

	//	// ������ phone_book_200 � ������� ������������ ����������� �� ������� phone_book_100 (������ ����� �� ������ ������)
	//	Phone_Book_Item phone_book_200(phone_book_100);

	//	// auto - �������������� ���������� ���� ������ ������������
	//	auto val = phone_book_200.Test(phone_book_100);

	//	Phone_Book_Item phone_book_300;
	//	phone_book_300 = phone_book_200;

	//	phone_book_100.Set_Phone_Number("99676767");

	//	// ���������� ������������
	//	phone_book_300 = phone_book_200 = phone_book_100;



	//char* cText1 = new char[10] {};
	//strcpy_s(cText1, 10, "Dfg");

	//// ������ ������� � ������ � ����, ��������� � ������ 21 [��� ������!]
	//cText1 = new char[10] {};

	//delete[] cText1;

	//char* cText2 = cText1;

	//strcpy_s(cText2, 10, "5673737");

	//delete[] cText2;

	//cText2 = nullptr;



	//// ������ � ���� � ����� � ["allocation" - ������������� ������ (��������� ������) � ����]
	//char* Name = (char*)malloc(20);
	//if (!Name) return -1;
	//memset(Name, 0, 20);

	//// string copy ������� � ����������� ����� [Name = "abc"]
	//strcpy_s(Name, 20, "abc");

	//// ��������� ������������� ������ ��� ���������� ����� � ������ ������ � �
	//Name = (char*)realloc(Name, 24);
	//if (!Name) return -1;

	//// ������������ (��������) ��������� Name � ����� �
	//free(Name);



	//Monkey* Ab = new Monkey;

	//delete Ab;



	// AbstractClass First;
	// int x1 = First.GetVal();

	Structure1 Second;
	int x2 = Second.GetVal();

	FromStruct1 ObjectFromStruct1;

	// AbstractClass* Third1 = &First;

	// int x3 = Third1 -> GetVal();

	// Third1 = &Second;

	// int x4 = Third1 -> GetVal();

	// ������ ������������
	AbstractClass* Array[2]{ &ObjectFromStruct1, &Second };

	int A1 = Array[0]->GetVal();
	int A2 = Array[1]->GetVal();


	// AbstractClass Third2 = *Third1;

	NextClass Next1;
	Next1.BaseClass1::Test();

	Homosapiens Sapience;

	int x = 1;
	int y = 2;

	//Swap(x, y);

	//std::cout << "Swap x and y:" << "\n";
	//std::cout << x << "\n";
	//std::cout << y << "\n";

	// ��������� "����" �� ����������� ���������� �++ � ������ � �������������
	// std::pair<float, float> Centr = std::make_pair(1, 2);
	// float x = Centr.first, y = Centr.second;
	// auto [x2, y2] = Centr;



	TestClass_1* TestObj_1 = TestClassFactory();



	// ���� static ������ ������ ���������� ���� ���� ��� �� ������ ������� ����� ������, ���� �������� ���������.
	std::cout << TestClass_2::count;

	TestClass_2 TestObj_2_1, TestObj_2_2, TestObj_2_3;

	std::cout << TestClass_2::count;



	// const char* str1[] = { "Hello", "World!" };
	// char str2[20]{};
	// strcpy(str2, str1[0]);
	// strcat(str2, str1[1]); // ������������ ����� ("��������" �����)
	// int iRes1 = strcmp(str1[0], "Hello"); // ���������� ������, ���� ������ �����, ������ 0, ���� ������ ������ => <0, ���� ������ => >0
	// int iRes2 = strcmp(str1[0], "World!");

	// int iRes3 = memcmp(str1[0], "dgdg", 4);

	// stricmp();
	// _memicmp();




	Rect Rect_1;
	Rect_1.SetCords(0, 0, 10, 10);
	Rect_1.FileWrite();
	Rect_1.FileRead();
	Circle Circle_1;
	Circle_1.FileRead();

	Rect_1.Save("SavedRect.txt");


	int TagfileLen = 0;
	char* buffer = ReadBINFile("Tag.mp3", TagfileLen);

	ID3v24Header* pID3v24Header = ReadHeader("Tag.mp3");

	TestException();

	TestColor(_ColorType::red);

	Exceptions();

	//TestSEH();

	int value = 10;
	float value2 = 12345 * 0.35784f;
	std::cout << std::boolalpha;
	std::cout << "\n" << isEven(value) << "\n";
	std::cout << isEven2(value) << "\n";
	std::cout << isEven3(10.0f) << "\n";

	// ��������� ������ "�������" - ����� ����� �������
	std::cout << getM(value2) << "\n";
	
	// ���������� "����"
	std::cout << int(value2) << "\n";

	// ���������� � ����������
	std::cout << int(value2+0.5f) << "\n";

	std::cout << value2 << "\n";
	std::cout << std::noboolalpha;




	//int64_t iLen = 0x10'000'000;
	//int64_t iTailLen = 0x1'000'000;

	//ChronoTest(10, trimRight_simple1, iLen, iTailLen, "simple1");
	//ChronoTest(10, trimRight_simple2, iLen, iTailLen, "simple2");
	//ChronoTest(10, trimRight, iLen, iTailLen, "best");

	
}