#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/stat.h>

using namespace std;

// int Array_1[] == int* Array_1;
// int Array_2[10]{}; локальный (стековый) массив == автоматическая память
// int* Array_3 = new int[10]{}; heap == динамическая память == куча
// pointer - "Указатель"
// invalid pointer - "Невалидный указатель" или "Нулевой указатель" ("битый")
// void func(int arc, ...) - функция с переменным числом параметров и разным типом параметров

struct Test_Struct
{
    int x = 0, y = 0;
};

string Func_String(char* a, char* b)
{
    std::string a2(a), b2(b);
    return a2 + b2;
}

void Func_Test_Struct(Test_Struct& X) // Reference "ссылка" - передача объекта структуры Х по ссылке
{
    X.x = 10;
    X.y = 20;
}

void input_output()
{
    int a = 0;
   float b = 0;

    scanf("%d%f", &a, &b); // ввод с клавиатуры, "%d" - спецификация ввода целого числа, "%f" - ввод числа с плавающей точкой "float" и тд
}

vector<int> Array_Function_OnlyEven_Vector(int iLen)
{
    vector<int> intVector(iLen);

    for (int i = 0, k = 0; k < iLen; i++)
        if (i % 2 == 0) intVector[k] = i, k++;

    return intVector;
}

int* Array_Function_OnlyEven(int iLen)
{
    int* Array = new int[iLen]{};

    if (!Array) return nullptr;

    for (int i = 0, k = 0; k < iLen; i++)
        if (i % 2 == 0) Array[k] = i, k++;

    return Array;
}

int* Array_Function_EveryThird(int iLen)
{
    int* Array = new int[iLen]{};

    if (!Array) return nullptr;

    for (int i = 0, k = 0; k < iLen; i++)
        if ((i + 1) % 3 == 0) Array[k] = i, k++;

    return Array;
}

void Test()
{   
    int maxVal = max(1, 4); // максимум двух чисел
}

void Min_Max()
{
    int aMin = 0, bMin = 0, cMax = 0, dMax = 0;

    cout << "\n";
    cout << "Min_Max parameters:" << "\n";
    cout << "aMin = ";
    cin >> aMin;
    cout << "bMin = ";
    cin >> bMin;
    cout << "cMax = ";
    cin >> cMax;
    cout << "dMax = ";
    cin >> dMax;

    int valMin = min(aMin, bMin);

    int valMax = max(cMax, dMax);
    
    cout << "Min(" << aMin << " & " << bMin << ") = " << valMin << "\n";
    cout << "Max(" << cMax << " & " << dMax << ") = " << valMax << "\n";
}

int Max_Func(int a, int b)
{
    return (a > b) ? a : b; // ТЕРНАРНЫЙ ОПЕРАТОР ЗАМЕНА "if"
}

template <typename T> T Max_Func(T a, T b)  // Шаблонная функция, принимает тип в качестве параметра (имя типа здесь "Т")
{                                           // Для каждого конкретного типа компилятор подставит этот тип вместо "Т" и сделает двоичный код (для каждого типа свой двоичный код)
    return (a > b) ? a : b;
}

void Min_Max_from_the_Array(int* Array, int iLen)
{
    int valMin = Array[0], valMax = Array[0];

    for (int i = 0; i < iLen; i++)
    {
        valMin = min(valMin, Array[i]);
        valMax = max(valMax, Array[i]);
    }

    cout << "\n";
    cout << "Min_Max_from_the_Array:" << "\n";
    cout << "valMin = " << valMin << "\n";
    cout << "valMax = " << valMax << "\n";
}

int* Swap(int* p_intArray, uint32_t iLen, int Index1, int Index2) // Swap - фунция; (......) - формальные параметры функции
{
    if (!p_intArray || Index1 >= (int)iLen || Index2 >= int(iLen)) return nullptr;

    int iTemp = p_intArray[Index1];
    p_intArray[Index1] = p_intArray[Index2];
    p_intArray[Index2] = iTemp;

    return p_intArray;
}

template <typename T> vector<T> ShiftL_1_Function_Vector(vector<T> Array, T iLen)
{
    int iTemp = Array[0];

    for (int i = 0; i < (iLen - 1); i++)
        Array[i] = Array[i + 1];

    Array[iLen - 1] = iTemp;

    return Array;
}

int* ShiftL_1(int* Array, int iLen)
{
    if (!Array) return nullptr;

    int iTemp = Array[0];

    for (int i = 0; i < (iLen - 1); i++)
        Array[i] = Array[i + 1];

    Array[iLen - 1] = iTemp;

    return Array;
}

int* Shift_Right_1(int* Array, int iLen)
{
    if (!Array) return nullptr;

    int iTemp = Array[iLen-1];

    for (int i = (iLen-1); i > 0; i--)
        Array[i] = Array[i-1];

    Array[0] = iTemp;

    return Array;
}

int* ShiftL_N(int* Array, int iLen, int N)
{
    if (!Array) return nullptr;

    for (int i = 0; i < N; i++)
        ShiftL_1(Array, iLen);

    return Array;
}

void Cout_Function(string Text, int* Array, int iLen)
{
    cout << "\n";
    cout << Text << "\n";
    for (int i = 0; i < iLen; i++) cout << Array[i] << "\n";
}

int Average_Value_Func(int* Array, int iLen)
{
    float* x = (float*)Array;
    
    float xX = *x;
    int yY = *Array;

    if (!Array) return 0;

    int Average_Value = 0;

    for (int i = 0; i < iLen; i++) Average_Value += Array[i];

    return Average_Value / iLen;
}

template <typename T> T Average_Value_Func(std::vector<T> intVec)
// Сигнатура функции включает в себя: имя, параметр возвращаемый и параметр внутри (формальные параметры)
// Если две функции с одинаковым именем и рзными фомральными параметрами - они считаются разными, с разными сигнатурами
// Если функции отличаются только возвращаемым результатом, то компилятор их не отличает
{
    T Average_Value = 0;

    for (int i = 0; i < intVec.size(); i++)
        Average_Value += intVec[i];

    return Average_Value / intVec.size();
}

void Square_Array_Elements(int* Array, int iLen)
{
    if (!Array) return;

    for (int i = 0; i < iLen; i++) Array[i] = Array[i] * Array[i];

    Cout_Function("Squared elements Array:", Array, iLen);
}

void Temp(int val)
{
    val = 10; // val - ссылка на int
}


void To_Log_Internal(const char* filename, const char* buffer, int buffLen = 0) // "int buffLen = 0" здесь параметр по умолчанию равный нулю ("дефолтный")
{
    int file_handle;
    if (_sopen_s(&file_handle, filename, O_WRONLY | O_APPEND | O_CREAT, _SH_DENYNO, S_IREAD | S_IWRITE)) return;
    if (!buffLen) buffLen = (int)strlen(buffer);
    _write(file_handle, buffer, buffLen);
    _close(file_handle);
}

char* ReadBINFile(const char* fileName, int& fileLen)
{
    struct _stat FileStat;
    int file_handle;
    if (_sopen_s(&file_handle, fileName, O_RDONLY | O_BINARY, _SH_DENYNO, S_IREAD)) return nullptr;
    _fstat(file_handle, &FileStat);
    fileLen = FileStat.st_size;
    char* buffer = new char[fileLen + 1] {};
    _read(file_handle, buffer, fileLen);
    _close(file_handle);
    return buffer;
}

void To_Log(const char* filename, const char* msgBuff, ...)
{
    char workBuff[1000];
    va_list argptr;
    va_start(argptr, msgBuff);
    vsprintf_s(workBuff, msgBuff, argptr);
    va_end(argptr);
    To_Log_Internal(filename, workBuff);
}


int Task1()
{
    int val = 5;
    Temp(val);

    To_Log("Log.txt", "Text:%i,%f,%s,%i\n", 10, 12.5, "OK", 5);

    Test_Struct tS1;

    Func_Test_Struct(tS1);

    cout << Func_String((char*)"a", (char*)"b") << "\n";

   // input_output();

    std::vector<float> intVector = { 1, 2, 4, 6 };

    float intValVec = Average_Value_Func(intVector);

    int valMax_Func_i = Max_Func<int>(10, 11);
    double valMax_Func_d = Max_Func<double>(10, 11);

    int iLen = 0;

    cout << "Array Length: iLen = ";
    cin >> iLen;

    int* Array_OnlyEven = Array_Function_OnlyEven(iLen);



    if (!Array_OnlyEven) return 0;

    Cout_Function("Array_OnlyEven:", Array_OnlyEven, iLen);

    
    vector<int> Array_OnlyEven_Vector = Array_Function_OnlyEven_Vector(iLen);
    cout << "\nArray_OnlyEven_Vector:\n";
    for (int i = 0; i < iLen; i++) cout << Array_OnlyEven_Vector[i] << "\n";


    if (!Swap(Array_OnlyEven, iLen, 1, 2))  // (...) - фактические (actual) параметры вызова функции
    {
        delete[]Array_OnlyEven;
        cout << "Swap returned 0";
        return 0;
    }

    Cout_Function("Array_OnlyEven Swap:", Array_OnlyEven, iLen);

    if (!ShiftL_N(Array_OnlyEven, iLen, 1))
    {  
        delete[]Array_OnlyEven;
        cout << "ShiftL_1 returned 0";
        return 0;
    }

    Cout_Function("ShiftL_N:", Array_OnlyEven, iLen);


    vector<int> ShiftL_1_Vector = ShiftL_1_Function_Vector(Array_OnlyEven_Vector, iLen);
    cout << "\nShiftL_1_Vector:\n";
    for (int i = 0; i < iLen; i++) cout << ShiftL_1_Vector[i] << "\n";


    delete[] Array_OnlyEven;

    int* Array_EveryThird = Array_Function_EveryThird(iLen);

    if (!Array_EveryThird) return 0;

    Cout_Function("Array_EveryThird:", Array_EveryThird, iLen);

    Min_Max_from_the_Array(Array_EveryThird, iLen);

    cout << "\nAverage_Value = " << Average_Value_Func(Array_EveryThird, iLen) << "\n";

    Square_Array_Elements(Array_EveryThird, iLen);

    Shift_Right_1(Array_EveryThird, iLen);

    Cout_Function("Array_EveryThird shifted right 1 step:", Array_EveryThird, iLen);

    delete[] Array_EveryThird;

    Min_Max();

    return 1;
}