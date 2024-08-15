// RAII "Resource Acquisition Is Initialization"

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>


// ����� - "�������" ������ ��������� ���������
// ��� �������� ���������� ������ ��������� ������������� ���������, � ��� ����������� ���������� ������ ������������� ���������
// ������� ���� �������� ������ - ��������� �������� ����������, �� ��� ������ �� ������� ������������� ��������� ������
// ������: 1) ��� ������ � ������������ ������� �������� 2) �������� ������� �������

namespace RAII

{
	template<typename T> class RAII_memory_wrap
	{
	private:
		// ���������� ���������
		T* pData = nullptr;
	public:
		RAII_memory_wrap()
		{
			// �������������� ������������� ����������� ��������� � ������������ �� ���������
			pData = new T();
		};
		~RAII_memory_wrap()
		{
			// �������������� �������� ��������� � ������ �����������
			delete pData;
		};
		T* GetData()
		{
			// ������ � ��������� (� ������ �� ������� �� ���������)
			return pData;
		}
	};

	struct TestStruct
	{
		int x = 0;
		int y = 0;
		TestStruct()
		{
			std::cout << "TestStruct constructor\n";
		}
		~TestStruct()
		{
			std::cout << "TestStruct destructor\n";
		}
	};

	void TestRAII();


	
	class RAII_file_wrap
	{
	private:

		char FileName[20];
		char buffer[20];
		int buffLen = 0;

		void FileWriteInternal(char* FileName, char* buffer, int buffLen)
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

		RAII_file_wrap()
		{
			std::cout << "\nFileName: ";
			scanf("%19s", FileName);
			std::cout << "\nbuffer: ";
			scanf("%19s", buffer);
			std::cout << "\nbuffLen = ";
			std::cin >> buffLen;


			FileWriteInternal(FileName, buffer, buffLen);
		};
		
		~RAII_file_wrap()
		{
			int i = 0;
			while (FileName[i])
			{
				FileName[i] = '\0';
				i++;
			};
			i = 0;
			while (buffer[i])
			{
				buffer[i] = '\0';
				i++;
			};
		};
	};

	void TestRAII_file();



	class RAII_file_wrap_2
	{

	protected:

		FILE* file = nullptr;

		std::string FileName;

	public:

		RAII_file_wrap_2(std::string FileName, std::string Mode);

		~RAII_file_wrap_2();

		size_t Write(const void* buffer, size_t buffLen);

		size_t Read(void* buffer, size_t buffLen);
		
		std::string Get_FileName();
	};

	void TestRAII_file_2();

	class RAII_file_wrap_3 : public RAII_file_wrap_2
	{

	public:

		FILE* Get_FileDescriptor()
		{
			return file;
		}

	};
};