#include <string>

// ������ "���-�������".
// ���� ��� ���������� ������� - ��� "��������".
// "���������� ��������" - ����� ������� (���� �� ���������).
uint32_t HashFunc(const char* text)
{
	uint32_t textLen = (uint32_t)strlen(text);
	uint32_t result = 0;
	for (uint32_t i = 0; i < textLen; i++)
	{
		result += text[i];
	}
	result &= 0x3ff; // "&=" - �������������� and.
	return result;
}