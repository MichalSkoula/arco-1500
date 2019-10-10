#include "Arduino.h"

#include <chrono>
#include <thread>

SerialPort Serial;

bool bitRead(byte b, byte bit)
{
	// TODO typ b
	return b & (1 << bit);
}

void bitWrite(byte &b, byte bit, bool on)
{
	// TODO typ b
    b = (b & ~(1 << bit)) | (on << bit);
}

// TODO const static pole
int pinToScanCode(int pin)
{
    // see gamelib/input.h Pins enum
    switch (pin) {
        case 3:  return SDL_SCANCODE_S;
        case 2:  return SDL_SCANCODE_A;
        case 12: return SDL_SCANCODE_LEFT;
        case 11: return SDL_SCANCODE_UP;
        case 10: return SDL_SCANCODE_RIGHT;
        case 8:  return SDL_SCANCODE_DOWN;
        case 9:  return SDL_SCANCODE_KP_0;
        default: return -1;
    }
}

// all pins are now PULLUP
bool isPinPullUp(int pin)
{
    UNUSED(pin);
    return true;
}

byte readPin(int pin)
{
	int scanCode = pinToScanCode(pin);
	if (!pressedKeys || scanCode == -1)
		return LOW;
	return pressedKeys[scanCode] ? HIGH : LOW;
}

// TODO pinToScanCode2 - for alternate controls? wsad? numpad?

byte analogRead(int pin)
{
    UNUSED(pin);
	// TODO impl
	// at the moment only used as RNG seed
	return LOW;
}

byte digitalRead(int pin)
{
	byte value = readPin(pin);
	if (isPinPullUp(pin))
		return value == LOW ? HIGH : LOW;
	return value;
}

void pinMode(int pin, int mode)
{
    UNUSED(pin); UNUSED(mode);
	// at the moment hardcoded in isPinPullUp
	// TODO read from file (together with key mapping)?
}

void delay(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

uint32_t millis()
{
    static auto start = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
    return static_cast<uint32_t>(diff.count());
}

void randomSeed(unsigned int seed)
{
	srand(seed);
}

long int random(long int max)
{
	return rand() % max;
}

long int random(long int min, long int max)
{
	return min + rand() % (max - min);
}

void tone(int pin, int pitch, int ms)
{
    UNUSED(pin); UNUSED(pitch); UNUSED(ms);
	// TODO impl
}
