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

int Array_1[10]; // глобальный массив - глобальная память

void Func_1()
{
	// int Array[] == int*Array
	int Array_2[10]{ 0 }; // локальный (стековый) массив - автоматическая память
	int* Array_3 = new int[10] {0}; // heap == динамическая память == куча
}

int* Func_2(int iLen)
{
	int* Array = new int[iLen] {0};

	for (int i = 0; i < iLen; i++) Array[i] = i + 1;

	return Array;
}

// Статическая глобальная переменная.
static int iGlobalStatic = 10;

// Глобальная переменна.
int iGlobal = 11;

// Для каждого статического поля в классах требуется написать отдельно:
int TestClass_2::count;


// Классы
int Classes_Func();

Phone_Book_Item TestMoveConstructor()
{
	Phone_Book_Item phone_book("Vasya", "Ffgdg", "353665");

	return phone_book;
}

// Вариант обмена переменных без временного значения.
void Swap(int& x, int& y)
{
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
}

// zero rule - правило нуля (не нужны конструкторы копирования: все работает автоматически)
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

// trailing type - хвостовой тип
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

	//	// перенос объекта phone_book_1 класса Phone_Book_Item с помощью std::move()
	//	// Phone_Book_Item phone_book_1 = std::move(TestMoveConstructor());

	//	Phone_Book_Item phone_book_1("Vasya", "Ffgdg", "353665");

	//	Phone_Book_Item phone_book_2 = phone_book_1; 

	//	Phone_Book_Item phone_book_3;
	//	phone_book_3 = Phone_Book_Item("A111", "B222", "999999");

	//	phone_book_3 = 25;

	//	//Classes_Func();

	//	Phone_Book_Item phone_book_100("Sasha", "Antipin", "23742947242098");

	//	// std::cout << phone_book_100.Get_Name();

	//	// объект phone_book_200 с помощью конструктора копирования из объекта phone_book_100 (полная копия по новому адресу)
	//	Phone_Book_Item phone_book_200(phone_book_100);

	//	// auto - автоматическое вычисление типа данных компилятором
	//	auto val = phone_book_200.Test(phone_book_100);

	//	Phone_Book_Item phone_book_300;
	//	phone_book_300 = phone_book_200;

	//	phone_book_100.Set_Phone_Number("99676767");

	//	// цепочечное присваивание
	//	phone_book_300 = phone_book_200 = phone_book_100;



	//char* cText1 = new char[10] {};
	//strcpy_s(cText1, 10, "Dfg");

	//// потеря доступа к памяти в куче, созданной в строке 21 [это ошибка!]
	//cText1 = new char[10] {};

	//delete[] cText1;

	//char* cText2 = cText1;

	//strcpy_s(cText2, 10, "5673737");

	//delete[] cText2;

	//cText2 = nullptr;



	//// память в куче в стиле С ["allocation" - распределение памяти (выделение памяти) в куче]
	//char* Name = (char*)malloc(20);
	//if (!Name) return -1;
	//memset(Name, 0, 20);

	//// string copy функция С копирования строк [Name = "abc"]
	//strcpy_s(Name, 20, "abc");

	//// повторное распределение памяти для имеющегося блока в другой размер в С
	//Name = (char*)realloc(Name, 24);
	//if (!Name) return -1;

	//// освобождение (удаление) указателя Name в стиле С
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

	// пример полиморфизма
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

	// Структура "Пара" из Стандартной библиотеки С++ и пример её использования
	// std::pair<float, float> Centr = std::make_pair(1, 2);
	// float x = Centr.first, y = Centr.second;
	// auto [x2, y2] = Centr;



	TestClass_1* TestObj_1 = TestClassFactory();



	// Поле static внутри класса существует даже если нет ни одного объекта этого класса, пока работает программа.
	std::cout << TestClass_2::count;

	TestClass_2 TestObj_2_1, TestObj_2_2, TestObj_2_3;

	std::cout << TestClass_2::count;



	// const char* str1[] = { "Hello", "World!" };
	// char str2[20]{};
	// strcpy(str2, str1[0]);
	// strcat(str2, str1[1]); // конкатенация строк ("сложение" строк)
	// int iRes1 = strcmp(str1[0], "Hello"); // сравнивает строки, если строки равны, вернет 0, если первая меньше => <0, если больше => >0
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

	// выделение только "мантисы" - числа после запятой
	std::cout << getM(value2) << "\n";
	
	// округление "вниз"
	std::cout << int(value2) << "\n";

	// округление к ближайшему
	std::cout << int(value2+0.5f) << "\n";

	std::cout << value2 << "\n";
	std::cout << std::noboolalpha;




	//int64_t iLen = 0x10'000'000;
	//int64_t iTailLen = 0x1'000'000;

	//ChronoTest(10, trimRight_simple1, iLen, iTailLen, "simple1");
	//ChronoTest(10, trimRight_simple2, iLen, iTailLen, "simple2");
	//ChronoTest(10, trimRight, iLen, iTailLen, "best");

	
}