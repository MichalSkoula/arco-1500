#ifndef GAMELIB_DISPLAY_H
#define GAMELIB_DISPLAY_H

#include <Arduino.h>
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

#endif	/* GAMELIB_DISPLAY_H */
