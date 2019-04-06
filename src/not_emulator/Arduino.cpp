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

/*
enum Pins {
	START_BUTTON_PIN 	= 13,
	ACTION_BUTTON_PIN 	= 12,

	LEFT_BUTTON_PIN 	= 6,
	UP_BUTTON_PIN 		= 5,
	RIGHT_BUTTON_PIN 	= 4,
	DOWN_BUTTON_PIN 	= 2,
	CENTER_BUTTON_PIN 	= 3,

	BUZZER_PIN 			= 11
};
*/

// TODO const static pole
int pinToScanCode(int pin)
{
	switch (pin) {
		case 13: return SDL_SCANCODE_S;
		case 12: return SDL_SCANCODE_A;
		case 6:  return SDL_SCANCODE_LEFT;
		case 5:  return SDL_SCANCODE_UP;
		case 4:  return SDL_SCANCODE_RIGHT;
		case 2:  return SDL_SCANCODE_DOWN;
		case 3:  return SDL_SCANCODE_KP_0;
		default: return -1;
	}
}

bool isPinPullUp(int pin)
{
	switch (pin) {
		case 13:
		case 12: return false;

		case 6:
		case 5:
		case 4:
		case 2:
		case 3:  return true;

		default: return false;
	}
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
