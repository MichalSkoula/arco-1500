#ifndef _GAMELIB_H
#define _GAMELIB_H

#include <U8g2lib.h>

// The LED display (does not send AC)
class Display : public U8G2_SSD1306_128X64_NONAME_1_HW_I2C
{
public:
	Display();
	
	// font must be set manually
	void drawText(int x, int y, const String &text);
	
	// sets font to big/small
	// TODO template?
	// TODO nevolat setFont pokud se nezměnil?
	void drawBigText(int x, int y, const String &text);
	void drawSmallText(int x, int y, const String &text);
	
private:
	void drawText(const uint8_t *font, int x, int y, const String &text);
};

extern Display display;

// 128x64 pixels
constexpr byte DISPLAY_WIDTH = 128;
constexpr byte DISPLAY_HEIGHT = 64;

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

enum Buttons {
	START_BUTTON 	= 0,
	ACTION_BUTTON	= 1,
	
	LEFT_BUTTON		= 2,
	UP_BUTTON		= 3,
	RIGHT_BUTTON	= 4,
	DOWN_BUTTON		= 5,
	CENTER_BUTTON	= 6
};

enum InitFlags {
	BUTTONS 	= 1,
	JOYSTICK 	= 2,
	SOUND 		= 4,
	INIT_ALL 	= 0xFF
};

// called in setup() with ORed mask of desired init flags
void initGame(byte initFlags);

bool buttonDown(byte button);

// read and update button state
// return true when the button is pressed and then always false until
// the button is released and pressed again
// should not be called more than once per button per loop()
// for classical buttons loop() should have at least 3 ms of delay to filter out fake release
bool buttonPressed(byte button);

// play tone for 10 ms by default
void playTone(int pitch, int time = 10);

#endif	/* _GAMELIB_H */
