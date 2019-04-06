#ifndef NOT_EMULATOR_EEPROM_H
#define NOT_EMULATOR_EEPROM_H

#include <cstdio>
#include <cstring>

class EEPROMemory
{
public:
	using memory_t = unsigned char;
	static constexpr size_t SIZE = 512;
	static constexpr char const *FILENAME = "eeprom.bin";

	EEPROMemory()
	{
		FILE *file = fopen(FILENAME, "rb");
		if (file) {
			fread(memory, sizeof(memory_t), SIZE, file);
		} else {
			memset(memory, 0, SIZE);
		}
	}

	~EEPROMemory()
	{
		FILE *file = fopen(FILENAME, "wb");
		if (file) {
			fwrite(memory, sizeof(memory_t), SIZE, file);
		}
	}

	template<typename T>
	T & get(int index, T &t)
	{
		memcpy(&t, memory + index, sizeof(T));
		return t;
	}

	template<typename T>
	const T & put(int index, const T &t)
	{
		memcpy(memory + index, &t, sizeof(T));
		return t;
	}

private:
	memory_t memory[SIZE];
};

extern EEPROMemory EEPROM;

#endif	/* NOT_EMULATOR_EEPROM_H */
