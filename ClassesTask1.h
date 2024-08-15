#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include "Global.h"

// ��������� ���� std::pair<float, float>
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

	// ����� �����������
	void copyFrom(Rect& R)
	{
		x1 = R.x1;
		y1 = R.y1;
		x2 = R.x2;
		y2 = R.y2;
	}

	// ����� ��������
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

		// fopen_s ������� ���� � ������ ������ "�+" - append "���� ����� �� ����������, �� ��������", ���� ���� �� ������ �������, ������ ��� ������
		errno_t err = fopen_s(&file, FileName, "a+");

		if (err || !file) return;

		// strlen(buffer) ���� ����� ������ ���� �� ������, ��������� �������� ����� ������
		if (!buffLen) buffLen = (int)strlen(buffer);

		// fwrite ������ ������ � ���� (������ �������� ������ 1)
		size_t realSize = fwrite(buffer, 1, buffLen, file);

		// fclose(file) ��������� ����, ��� ����� ����������� ���������� � ��������� ���������� ����� ������������ ������� �� ����. 
		fclose(file);
	}

public:

	// �����������
	Rect() = default;

	// ����������� ��� ������� ���� ���������
	Rect(float x1, float y1, float x2, float y2)
	{
		SetCords(x1, y1, x2, y2);
	}

	// ����������� ����������� (����������� ����������� �����������) ��� const
	Rect(const Rect& From)
	{
		copyFrom((Rect&)From);
	}

	// ����������� ����������� (����������� ����������� �����������)
	Rect(Rect& From)
	{
		copyFrom((Rect&)From);
	}

	// ����������� ��������
	Rect(Rect&& From) noexcept
	{
		moveFrom((Rect&&)From);
	}

	// �������� �����������-������������
	Rect& operator=(Rect& R)
	{
		if (&R == this) return *this;

		copyFrom(R);

		return *this;
	}

	// �������� �����������-������������
	Rect& operator=(Rect&& From) noexcept
	{
		if (&From == this) return *this;

		moveFrom((Rect&&)From);

		return *this;
	}

	// "������"
	std::tuple<float, float, float, float> GetCords()
	{
		return std::make_tuple(x1, y1, x2, y2);
	}

	// "������"
	void SetCords(float x1, float y1, float x2, float y2)
	{
		Rect::x1 = x1;
		Rect::y1 = y1;
		Rect::x2 = x2;
		Rect::y2 = y2;
	}


	// ���������� ������ ���������� ��� ������ Rect:

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


	// ������� ��� ����������:

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

		// sprintf_s ������������ ������������ "..."  � ����������� x1... � ��������� ����� (������ char)
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

	// friend - �������� �����, ����������� ������ ������� (��� ������� ������) � ���������� ������ ������
	friend std::ostream& operator<<(std::ostream& Out, Rect& R);
};

// ������� ���������� ���������� ��� ���� ������ ��� Rect:

Rect operator-(Rect& L, Rect& R)
{
	auto [Lx1, Ly1, Lx2, Ly2] = L.GetCords();
	auto [Rx1, Ry1, Rx2, Ry2] = R.GetCords();

	return Rect(Lx1 - Rx1, Ly1 - Ry1, Lx2 - Rx2, Ly2 - Ry2);
}

// ������������� �������� ���������� ������ ��� ���� ������ ��� Rect:
std::ostream& operator<<(std::ostream& Out, Rect& R)
{
	auto [Rx1, Ry1, Rx2, Ry2] = R.GetCords();

	// ����� ���:
	return Out << Rx1 << ", " << Ry1 << ", " << Rx2 << ", " << Ry2 << "\n";

	// ����� � ���:
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

	// ����� �����������
	void copyFrom(Circle& R)
	{
		x = R.x;
		y = R.y;
		r = R.r;
	}

	// ����� ��������
	void moveFrom(Circle&& From) noexcept
	{
		x = From.x; From.x = 0;
		y = From.y; From.y = 0;
		r = From.r; From.r = 0;
	}

public:

	// �����������
	Circle() = default;

	// ����������� ������� ��������� � �������
	Circle(float x, float y, float r) :
		x(x), y(y), r(r)
	{
		if (!checkCords()) throw 0;
	}

	// ����������� ����������� (����������� ����������� �����������) ��� const
	Circle(const Circle& From)
	{
		copyFrom((Circle&)From);
	}

	// ����������� ����������� (����������� ����������� �����������)
	Circle(Circle& From)
	{
		copyFrom((Circle&)From);
	}

	// ����������� ��������
	Circle(Circle&& From) noexcept
	{
		moveFrom((Circle&&)From);
	}

	// �������� �����������-������������
	Circle& operator=(Circle& R)
	{
		if (&R == this) return *this;

		copyFrom(R);

		return *this;
	}

	// �������� �����������-������������
	Circle& operator=(Circle&& From) noexcept
	{
		if (&From == this) return *this;

		moveFrom((Circle&&)From);

		return *this;
	}

	// "������"
	std::tuple<float, float, float> GetCordsAndRadius()
	{
		return std::make_tuple(x, y, r);
	}

	// "������"
	void SetCordsAndRadius(float x, float y, float r)
	{
		Circle::x = x;
		Circle::y = y;
		Circle::r = r;
	}


	// ���������� ������ ���������� ��� ������ Circle:

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


	// ������� ����������:

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

// ������� ���������� ���������� ��� ���� ������ ��� Circle:

Circle operator-(Circle& L, Circle& R)
{
	auto [xL, yL, rL] = L.GetCordsAndRadius();
	auto [xR, yR, rR] = R.GetCordsAndRadius();

	return Circle(xL - xR, yL - yR, rL - rR);
}

// ������������� �������� ���������� ������ ��� ���� ������ ��� Circle:
std::ostream& operator<<(std::ostream& Out, Circle& R)
{
	auto [xR, yR, rR] = R.GetCordsAndRadius();

	// ����� ���:
	return Out << xR << ", " << yR << ", " << rR << "\n";

	// ����� � ���:
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
		// ����� ������� 1-2.
		float A12 = (float)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		// ����� ������� 2-3.
		float B23 = (float)sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
		// ����� ������� 1-3.
		float �13 = (float)sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));

		return std::make_tuple(A12, B23, �13);
	}

	// ����� �����������
	void copyFrom(Triangle& R)
	{
		x1 = R.x1;
		y1 = R.y1;
		x2 = R.x2;
		y2 = R.y2;
		x3 = R.x3;
		y3 = R.y3;
	}

	// ����� ��������
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

	// �����������
	Triangle() = default;

	// ����������� ������� ���������
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3) :
		x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3)
	{
		if (!checkCords()) throw 0;
	}

	// ����������� ����������� (����������� ����������� �����������) ��� const
	Triangle(const Triangle& From)
	{
		copyFrom((Triangle&)From);
	}

	// ����������� ����������� (����������� ����������� �����������)
	Triangle(Triangle& From)
	{
		copyFrom((Triangle&)From);
	}

	// ����������� ��������
	Triangle(Triangle&& From) noexcept
	{
		moveFrom((Triangle&&)From);
	}

	// ����������� �����������-������������
	Triangle& operator=(Triangle& R)
	{
		if (&R == this) return *this;

		copyFrom(R);

		return *this;
	}

	// ����������� �����������
	Triangle& operator=(Triangle&& From) noexcept
	{
		if (&From == this) return *this;

		moveFrom((Triangle&&)From);

		return *this;
	}

	// "������"
	std::tuple<float, float, float, float, float, float> GetCords()
	{
		return std::make_tuple(x1, y1, x2, y2, x3, y3);
	}

	// "������"
	void SetCords(float x1, float y1, float x2, float y2, float x3, float y3)
	{
		Triangle::x1 = x1;
		Triangle::y1 = y1;
		Triangle::x2 = x2;
		Triangle::y2 = y2;
		Triangle::x3 = x3;
		Triangle::y3 = y3;
	}


	// ���������� ������ ���������� ��� ������ Triangle:

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


	// ������� ����������:

	float CalcPerimetr()
	{
		auto [A12, B23, �13] = CalcABC();

		return A12 + B23 + �13;
	}

	float CalcSquare()
	{
		auto [A12, B23, �13] = CalcABC();

		float HalfTrianglePerimetr = (A12 + B23 + �13) / 2;

		float TriangleSquare = sqrt(HalfTrianglePerimetr * (HalfTrianglePerimetr - A12) * (HalfTrianglePerimetr - B23) * (HalfTrianglePerimetr - �13));

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

// ������� ���������� ���������� ��� ���� ������ ��� Rect:

Triangle operator-(Triangle& L, Triangle& R)
{
	auto [Lx1, Ly1, Lx2, Ly2, Lx3, Ly3] = L.GetCords();
	auto [Rx1, Ry1, Rx2, Ry2, Rx3, Ry3] = R.GetCords();

	return Triangle(Lx1 - Rx1, Ly1 - Ry1, Lx2 - Rx2, Ly2 - Ry2, Lx3 - Rx3, Ly3 - Ry3);
}

// ������������� �������� ���������� ������ ��� ���� ������ ��� Rect:
std::ostream& operator<<(std::ostream& Out, Triangle& R)
{
	auto [Rx1, Ry1, Rx2, Ry2, Rx3, Ry3] = R.GetCords();

	// ����� ���:
	return Out << Rx1 << ", " << Ry1 << ", " << Rx2 << ", " << Ry2 << ", " << Rx3 << ", " << Ry3 << "\n";

	// ����� � ���:
	// return Out << R.x1 << ", " << R.y1 << ", " << R.x2 << ", " << R.y2 << ", " << R.x3 << ", " << R.y3 << "\n";
}



// ������ ������ � ��������� ������������� � ������� Factory() ��� �������� ������� ����� ������.
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



// ������ ������ �� ����������� ����� (����������).
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