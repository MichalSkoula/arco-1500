#include "display.h"

Display::Display() : U8G2_SSD1306_128X64_NONAME_1_HW_I2C(U8G2_R0)
{}

void Display::drawText(int x, int y, const String &text)
{
	drawText(nullptr, x, y, text);
}

void Display::drawBigText(int x, int y, const String &text)
{
	drawText(u8g2_font_9x15_tf, x, y, text);
}

void Display::drawSmallText(int x, int y, const String &text)
{
	drawText(u8g2_font_5x7_tf, x, y, text);
}

void Display::drawText(const uint8_t *font, int x, int y, const String &text)
{
	if (font) {
		setFont(font);
	}
	setCursor(x, y);
	print(text);
}

Display display;
