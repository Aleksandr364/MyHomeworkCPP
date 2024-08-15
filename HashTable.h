#pragma once

#include <vector>
#include <string>

class HashTable
{
protected:

	struct HashTableItem
	{
		std::vector<std::string> chain;
		void add(const std::string text)
		{
			if (std::find(chain.begin(), chain.end(), text) == chain.end())
			{
				chain.push_back(text);
			}
		};
	};

	std::vector<HashTableItem> data;
	const uint32_t dataSize = 256;

	// Пример "хэш-функции".
	// Если два одинаковых индекса - это "коллизия".
	// "Разрешение коллизии" - метод цепочек (один из вариантов).
	uint32_t HashFunc(const char* text)
	{
		uint32_t textLen = (uint32_t)strlen(text);
		uint32_t result = 0;
		for (uint32_t i = 0; i < textLen; i++)
		{
			result += text[i];
		}
		//result &= 0x3ff; // "&=" - арифметический and.
		result &= 0xff;
		return result;
	}

public:

	HashTable()
	{
		data.reserve(dataSize);
		for (uint32_t i = 0; i < dataSize; i++)
		{
			data.push_back(HashTableItem());
		}
	};

	void add(const std::string text)
	{
		uint32_t index = HashFunc(text.c_str());
		data[index].add(text);
	}
};
