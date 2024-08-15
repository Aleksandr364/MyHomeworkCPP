#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include "Global.h"

// Псевдоним типа std::pair<float, float>
typedef std::pair<float, float> PairFloatType;



class Shape
{
public:

	Shape() = default;

	virtual float CalcPerimetr() = 0;

	virtual float CalcSquare() = 0;

	virtual void ChangeSize(float da, float db) = 0;

	virtual void Shift(float dx, float dy) = 0;

	virtual void FileWrite() = 0;

	virtual void FileRead() = 0;
};



class Rect : public Shape
{
protected:

	float x1, y1, x2, y2;

	bool checkCords()
	{
		return x1 >= 0 && y1 >= 0 && x2 > x1 && y2 > y1;
	}

	// метод копирования
	void copyFrom(Rect& R)
	{
		x1 = R.x1;
		y1 = R.y1;
		x2 = R.x2;
		y2 = R.y2;
	}

	// метод переноса
	void moveFrom(Rect&& From) noexcept
	{
		x1 = From.x1; From.x1 = 0;
		y1 = From.y1; From.y1 = 0;
		x2 = From.x2; From.x2 = 0;
		y2 = From.y2; From.y2 = 0;
	}

	void FileWriteInternal(const char* FileName, const char* buffer, int buffLen = 0)
	{
		FILE* file = nullptr;

		// fopen_s открыть файл в режиме записи "а+" - append "если файла не существует, он создаётся", если файл не сможет открыть, выдает код ошибки
		errno_t err = fopen_s(&file, FileName, "a+");

		if (err || !file) return;

		// strlen(buffer) если длина буфера явно не задана, посчитать реальную длину буфера
		if (!buffLen) buffLen = (int)strlen(buffer);

		// fwrite запись буфера в файл (второй аргумент всегда 1)
		size_t realSize = fwrite(buffer, 1, buffLen, file);

		// fclose(file) закрывает файл, тем самым освобождает дескриптор и выгружает внутренний буфер операционной системы на диск. 
		fclose(file);
	}

public:

	// конструктор
	Rect() = default;

	// конструктор для задания всех координат
	Rect(float x1, float y1, float x2, float y2)
	{
		SetCords(x1, y1, x2, y2);
	}

	// конструктор копирования (иллюстрация копирования компилятора) для const
	Rect(const Rect& From)
	{
		copyFrom((Rect&)From);
	}

	// конструктор копирования (иллюстрация копирования компилятора)
	Rect(Rect& From)
	{
		copyFrom((Rect&)From);
	}

	// конструктор переноса
	Rect(Rect&& From) noexcept
	{
		moveFrom((Rect&&)From);
	}

	// оператор копирования-присваивания
	Rect& operator=(Rect& R)
	{
		if (&R == this) return *this;

		copyFrom(R);

		return *this;
	}

	// оператор перемещения-присваивания
	Rect& operator=(Rect&& From) noexcept
	{
		if (&From == this) return *this;

		moveFrom((Rect&&)From);

		return *this;
	}

	// "геттер"
	std::tuple<float, float, float, float> GetCords()
	{
		return std::make_tuple(x1, y1, x2, y2);
	}

	// "сеттер"
	void SetCords(float x1, float y1, float x2, float y2)
	{
		Rect::x1 = x1;
		Rect::y1 = y1;
		Rect::x2 = x2;
		Rect::y2 = y2;
	}


	// перегрузка других операторов для класса Rect:

	Rect operator+(Rect& R)
	{
		return Rect(x1 + R.x1, y1 + R.y1, x2 + R.x2, y2 + R.y2);
	}

	Rect operator+=(Rect& R)
	{
		// int a = 0;
		// a += 10 == a = a + 10;

		x1 += R.x1, y1 += R.y1, x2 += R.x2, y2 += R.y2;

		return *this;
	}

	bool operator==(Rect& R)
	{
		return FloatEquality(GetH(), R.GetH()) && FloatEquality(GetW(), R.GetW());
	}

	bool operator!=(Rect& R)
	{
		return !operator==(R);
	}


	// функции для вычислений:

	float GetH()
	{
		return y2 - y1;
	}
	float GetW()
	{
		return x2 - x1;
	}

	float CalcPerimetr()
	{
		return (GetW() + GetH()) * 2;
	}

	float CalcSquare()
	{
		return GetH() * GetW();
	}
	
	void ChangeSize(float da, float db)
	{
		x2 += da;
		y2 += db;

		if (x2 < x1 || y2 < y1) throw 0;
	}
	
	void Shift(float dx, float dy)
	{
		x1 += dx;
		x2 += dx;

		y1 += dy;
		y2 += dy;

		if (x1 < 0 || y1 < 0) throw 0;
	}

	void FileWrite()
	{
		float RectPerimetr = CalcPerimetr();
		float RectSquare = CalcSquare();

		FILE* file = fopen("Rect.txt", "w");

		if (file)
		{
			fprintf(file, "RectPerimetr: %f\n", RectPerimetr);
			fprintf(file, "RectSquare: %f\n", RectSquare);
			fclose(file);
			printf("\nFile written successfully!\n");
		}
		else printf("\nFile writing failed!\n");
	}

	void Save(const char* FileName)
	{
		const int maxBuffLen = 1024;

		char buffer[maxBuffLen]{};

		// sprintf_s конвертирует спецификацию "..."  с переменными x1... в текстовый буфер (массив char)
		sprintf_s(buffer, maxBuffLen, "%f, %f, %f, %f\n", x1, y1, x2, y2);

		FileWriteInternal(FileName, buffer, (int)strlen(buffer));
	}

	void FileRead()
	{
		FILE* file = fopen("Rect.txt", "r");
		
		char line[100];

		if (file)
		{
			while (fgets(line, sizeof(line), file)) printf("%s", line);
			fclose(file);
			printf("File read successfully!\n");
		}
		else printf("\nFile reading failed!\n");
	}

	// friend - ключевое слово, разрешающее доступ функции (или другому классу) к защищенным частям класса
	friend std::ostream& operator<<(std::ostream& Out, Rect& R);
};

// примеры перегрузки операторов ВНЕ тела класса для Rect:

Rect operator-(Rect& L, Rect& R)
{
	auto [Lx1, Ly1, Lx2, Ly2] = L.GetCords();
	auto [Rx1, Ry1, Rx2, Ry2] = R.GetCords();

	return Rect(Lx1 - Rx1, Ly1 - Ry1, Lx2 - Rx2, Ly2 - Ry2);
}

// перегруженный оператор потокового вывода ВНЕ тела класса для Rect:
std::ostream& operator<<(std::ostream& Out, Rect& R)
{
	auto [Rx1, Ry1, Rx2, Ry2] = R.GetCords();

	// МОЖНО ТАК:
	return Out << Rx1 << ", " << Ry1 << ", " << Rx2 << ", " << Ry2 << "\n";

	// МОЖНО И ТАК:
	// return Out << R.x1 << ", " << R.y1 << ", " << R.x2 << ", " << R.y2 << "\n";
}



class Circle : public Shape
{
protected:

	float x, y, r;

	bool checkCords()
	{
		return x >= 0 && y >= 0 && r >= 0 && x - r >= 0 && y - r >= 0;
	}

	// метод копирования
	void copyFrom(Circle& R)
	{
		x = R.x;
		y = R.y;
		r = R.r;
	}

	// метод переноса
	void moveFrom(Circle&& From) noexcept
	{
		x = From.x; From.x = 0;
		y = From.y; From.y = 0;
		r = From.r; From.r = 0;
	}

public:

	// конструктор
	Circle() = default;

	// конструктор задания координат и радиуса
	Circle(float x, float y, float r) :
		x(x), y(y), r(r)
	{
		if (!checkCords()) throw 0;
	}

	// конструктор копирования (иллюстрация копирования компилятора) для const
	Circle(const Circle& From)
	{
		copyFrom((Circle&)From);
	}

	// конструктор копирования (иллюстрация копирования компилятора)
	Circle(Circle& From)
	{
		copyFrom((Circle&)From);
	}

	// конструктор переноса
	Circle(Circle&& From) noexcept
	{
		moveFrom((Circle&&)From);
	}

	// оператор копирования-присваивания
	Circle& operator=(Circle& R)
	{
		if (&R == this) return *this;

		copyFrom(R);

		return *this;
	}

	// оператор перемещения-присваивания
	Circle& operator=(Circle&& From) noexcept
	{
		if (&From == this) return *this;

		moveFrom((Circle&&)From);

		return *this;
	}

	// "геттер"
	std::tuple<float, float, float> GetCordsAndRadius()
	{
		return std::make_tuple(x, y, r);
	}

	// "сеттер"
	void SetCordsAndRadius(float x, float y, float r)
	{
		Circle::x = x;
		Circle::y = y;
		Circle::r = r;
	}


	// перегрузка других операторов для класса Circle:

	Circle operator+(Circle& R)
	{
		return Circle(x + R.x, y + R.y, r + R.r);
	}

	Circle operator+=(Circle& R)
	{
		// int a = 0;
		// a += 10 == a = a + 10;

		x += R.x, y += R.y, r += R.r;

		return *this;
	}

	bool operator==(Circle& R)
	{
		return FloatEquality(r, R.r);
	}

	bool operator!=(Circle& R)
	{
		return !operator==(R);
	}


	// функции вычисления:

	float CalcPerimetr()
	{
		return (float)2 * (float)3.14 * r;
	}

	float CalcSquare()
	{
		return (float)3.14 * r * r;
	}
	
	void ChangeSize(float da, float db)
	{
		float dr = 0;

		while (dr != da && dr != db)
		{
			std::cout << "Choose dr = " << da << " or " << db << "\n";
			std::cin >> dr;
		}

		r += dr;

		if (r < 0 || x - r < 0 || y - r < 0) throw 0;
	}

	void Shift(float dx, float dy)
	{
		x += dx;
		y += dy;

		if (x - r < 0 || y - r < 0) throw 0;
	}

	void FileWrite()
	{
		float CirclePerimetr = CalcPerimetr();
		float CircleSquare = CalcSquare();

		FILE* file = fopen("Circle.txt", "w");

		if (file != NULL)
		{
			fprintf(file, "CirclePerimetr: %f\n", CirclePerimetr);
			fprintf(file, "CircleSquare: %f\n", CircleSquare);
			fclose(file);
			printf("\nFile written successfully!\n");
		}
		else printf("File writing failed!\n");
	}

	void FileRead()
	{
		FILE* file = fopen("Circle.txt", "r");

		char line[100];

		if (file != NULL)
		{
			while (fgets(line, sizeof(line), file)) printf("%s", line);
			fclose(file);
			printf("File read successfully!\n");
		}
		else printf("File reading failed!\n");
	}
};

// примеры перегрузки операторов ВНЕ тела класса для Circle:

Circle operator-(Circle& L, Circle& R)
{
	auto [xL, yL, rL] = L.GetCordsAndRadius();
	auto [xR, yR, rR] = R.GetCordsAndRadius();

	return Circle(xL - xR, yL - yR, rL - rR);
}

// перегруженный оператор потокового вывода ВНЕ тела класса для Circle:
std::ostream& operator<<(std::ostream& Out, Circle& R)
{
	auto [xR, yR, rR] = R.GetCordsAndRadius();

	// МОЖНО ТАК:
	return Out << xR << ", " << yR << ", " << rR << "\n";

	// МОЖНО И ТАК:
	// return Out << x.R << ", " << y.R << ", " << r.R << "\n";
}



class Triangle : public Shape
{
protected:

	float x1, y1, x2, y2, x3, y3;

	bool checkCords()
	{
		return x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 > 0 && x3 > 0 && y3 >= 0;
	}

	std::tuple<float, float, float> CalcABC()
	{
		// Длина стороны 1-2.
		float A12 = (float)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		// Длина стороны 2-3.
		float B23 = (float)sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
		// Длина стороны 1-3.
		float С13 = (float)sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));

		return std::make_tuple(A12, B23, С13);
	}

	// метод копирования
	void copyFrom(Triangle& R)
	{
		x1 = R.x1;
		y1 = R.y1;
		x2 = R.x2;
		y2 = R.y2;
		x3 = R.x3;
		y3 = R.y3;
	}

	// метод переноса
	void moveFrom(Triangle&& From) noexcept
	{
		x1 = From.x1; From.x1 = 0;
		y1 = From.y1; From.y1 = 0;
		x2 = From.x2; From.x2 = 0;
		y2 = From.y2; From.y2 = 0;
		x3 = From.x3; From.x3 = 0;
		y3 = From.y3; From.y3 = 0;
	}

public:

	// конструктор
	Triangle() = default;

	// конструктор задания координат
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3) :
		x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3)
	{
		if (!checkCords()) throw 0;
	}

	// конструктор копирования (иллюстрация копирования компилятора) для const
	Triangle(const Triangle& From)
	{
		copyFrom((Triangle&)From);
	}

	// конструктор копирования (иллюстрация копирования компилятора)
	Triangle(Triangle& From)
	{
		copyFrom((Triangle&)From);
	}

	// конструктор переноса
	Triangle(Triangle&& From) noexcept
	{
		moveFrom((Triangle&&)From);
	}

	// конструктор копирования-присваивания
	Triangle& operator=(Triangle& R)
	{
		if (&R == this) return *this;

		copyFrom(R);

		return *this;
	}

	// конструктор перемещения
	Triangle& operator=(Triangle&& From) noexcept
	{
		if (&From == this) return *this;

		moveFrom((Triangle&&)From);

		return *this;
	}

	// "геттер"
	std::tuple<float, float, float, float, float, float> GetCords()
	{
		return std::make_tuple(x1, y1, x2, y2, x3, y3);
	}

	// "сеттер"
	void SetCords(float x1, float y1, float x2, float y2, float x3, float y3)
	{
		Triangle::x1 = x1;
		Triangle::y1 = y1;
		Triangle::x2 = x2;
		Triangle::y2 = y2;
		Triangle::x3 = x3;
		Triangle::y3 = y3;
	}


	// перегрузка других операторов для класса Triangle:

	Triangle operator+(Triangle& R)
	{
		return Triangle(x1 + R.x1, y1 + R.y1, x2 + R.x2, y2 + R.y2, x3 + R.x3, y3 + R.y3);
	}

	Triangle operator+=(Triangle& R)
	{
		// int a = 0;
		// a += 10 == a = a + 10;

		x1 += R.x1, y1 += R.y1, x2 += R.x2, y2 += R.y2, x3 += R.x3, y3 += R.y3;

		return *this;
	}

	bool operator==(Triangle& R)
	{
		auto [A12, B23, C13] = CalcABC();
		auto [A12_R, B23_R, C13_R] = R.CalcABC();

		return FloatEquality(A12, A12_R) && FloatEquality(B23, B23_R) && FloatEquality(C13, C13_R);
	}

	bool operator!=(Triangle& R)
	{
		return !operator==(R);
	}


	// функции вычисления:

	float CalcPerimetr()
	{
		auto [A12, B23, С13] = CalcABC();

		return A12 + B23 + С13;
	}

	float CalcSquare()
	{
		auto [A12, B23, С13] = CalcABC();

		float HalfTrianglePerimetr = (A12 + B23 + С13) / 2;

		float TriangleSquare = sqrt(HalfTrianglePerimetr * (HalfTrianglePerimetr - A12) * (HalfTrianglePerimetr - B23) * (HalfTrianglePerimetr - С13));

		return TriangleSquare;
	}

	void ChangeSize(float da, float db)
	{
		y2 += da;
		x3 += db;

		if (y2 <= 0 || x3 <= 0) throw 0;
	}

	void Shift(float dx, float dy)
	{
		x1 += dx;
		y1 += dy;

		if (x1 < 0 || y1 < 0) throw 0;
	}

	void FileWrite()
	{
		float TrianglePerimetr = CalcPerimetr();
		float TriangleSquare = CalcSquare();

		FILE* file = fopen("Triangle.txt", "w");

		if (file != NULL)
		{
			fprintf(file, "TrianglePerimetr: %f\n", TrianglePerimetr);
			fprintf(file, "TriangleSquare: %f\n", TriangleSquare);
			fclose(file);
			printf("\nFile written successfully!\n");
		}
		else printf("File writing failed!\n");
	}

	void FileRead()
	{
		FILE* file = fopen("Triangle.txt", "r");

		char line[100];

		if (file != NULL)
		{
			while (fgets(line, sizeof(line), file)) printf("%s", line);
			fclose(file);
			printf("File read successfully!\n");
		}
		else printf("File reading failed!\n");
	}
};

// примеры перегрузки операторов ВНЕ тела класса для Rect:

Triangle operator-(Triangle& L, Triangle& R)
{
	auto [Lx1, Ly1, Lx2, Ly2, Lx3, Ly3] = L.GetCords();
	auto [Rx1, Ry1, Rx2, Ry2, Rx3, Ry3] = R.GetCords();

	return Triangle(Lx1 - Rx1, Ly1 - Ry1, Lx2 - Rx2, Ly2 - Ry2, Lx3 - Rx3, Ly3 - Ry3);
}

// перегруженный оператор потокового вывода ВНЕ тела класса для Rect:
std::ostream& operator<<(std::ostream& Out, Triangle& R)
{
	auto [Rx1, Ry1, Rx2, Ry2, Rx3, Ry3] = R.GetCords();

	// МОЖНО ТАК:
	return Out << Rx1 << ", " << Ry1 << ", " << Rx2 << ", " << Ry2 << ", " << Rx3 << ", " << Ry3 << "\n";

	// МОЖНО И ТАК:
	// return Out << R.x1 << ", " << R.y1 << ", " << R.x2 << ", " << R.y2 << ", " << R.x3 << ", " << R.y3 << "\n";
}



// Пример класса с приватным конструктором и функции Factory() для создания объекта этого класса.
class TestClass_1
{
	friend TestClass_1* TestClassFactory();

private:

	TestClass_1() = default;
};

TestClass_1* TestClassFactory()
{
	return new TestClass_1;
}



// Пример класса со статическим полем (переменной).
class TestClass_2
{
public:

	static int count;

	TestClass_2()
	{
		count++;
	};

	~TestClass_2()
	{
		count--;
	};
};