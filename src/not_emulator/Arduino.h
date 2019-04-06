#ifndef NOT_EMULATOR_ARDUINO_H
#define NOT_EMULATOR_ARDUINO_H

#include <stdint.h>
#include <string>
#include <SDL2/SDL.h>

#define UNUSED(x) (void)(x)

#define PROGMEM
// TODO "better" - no macro?
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

using byte = unsigned char;

enum PinLevel
{
	LOW 	= 0,
	HIGH	= 1
};

enum PinMode
{
	INPUT 			= 0,
	OUTPUT			= 1,
	INPUT_PULLUP	= 2
};

// TODO impl
class SerialPort
{
public:
	void begin(int) {}
};

extern SerialPort Serial;

class String
{
private:
	std::string m_str;

public:
	String(const char *str) : m_str(str) {}
	String(const std::string &str) : m_str(str) {}
	String(char c) { m_str = std::string(1, c);	}

	String(int n) { m_str = std::to_string(n); }
    String(unsigned int n) { m_str = std::to_string(n);	}

	operator std::string() const { return m_str; }
	operator const char *() const {	return m_str.c_str(); }

	// TODO do better
	template<typename T>
	String & operator +=(const T &t)
	{
		m_str += t;
		return *this;
	}

	String operator +(const String &t)
	{
		m_str += t.m_str;
		return *this;
	}

	template<typename T>
	String operator +(const T &t)
	{
		m_str += t;
		return *this;
	}
};

template<typename T>
String operator +(const T &l, const String &r)
{
	return String(l) + r;
}

bool bitRead(byte b, byte bit);
void bitWrite(byte &b, byte bit, bool on);

extern const Uint8 *pressedKeys;
byte analogRead(int pin);
byte digitalRead(int pin);
void pinMode(int pin, int mode);

void delay(int ms);

void randomSeed(unsigned int seed);

// random number between 0 and max - 1
long int random(long int max);

// random number between min and max - 1
long int random(long int min, long int max);

void tone(int pin, int pitch, int ms);

#endif	/* NOT_EMULATOR_ARDUINO_H */
