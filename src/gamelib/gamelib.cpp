#include "gamelib.h"

Display::Display() : U8G2_SSD1306_128X64_NONAME_1_HW_I2C(U8G2_R0)
{ 

}

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

void initGame(byte initFlags)
{
	if (initFlags & BUTTONS) {
		pinMode(START_BUTTON_PIN, INPUT);
  		pinMode(ACTION_BUTTON_PIN, INPUT);
	}
	if (initFlags & JOYSTICK) {
		pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
		pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
		pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
		pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
		pinMode(CENTER_BUTTON_PIN, INPUT_PULLUP);
	}
	if (initFlags & SOUND) {
		pinMode(BUZZER_PIN, OUTPUT);
	}
	
	display.begin();
	display.setBitmapMode(1);
	Serial.begin(9600);			// TODO optional?
	randomSeed(analogRead(0));
}

byte buttonPin(byte button)
{
	switch (button) {
		case START_BUTTON: 	return START_BUTTON_PIN;
		case ACTION_BUTTON: return ACTION_BUTTON_PIN;
		case LEFT_BUTTON: 	return LEFT_BUTTON_PIN;
		case UP_BUTTON: 	return UP_BUTTON_PIN;
		case RIGHT_BUTTON: 	return RIGHT_BUTTON_PIN;
		case DOWN_BUTTON: 	return DOWN_BUTTON_PIN;
		case CENTER_BUTTON: return CENTER_BUTTON_PIN;
	}
	// TODO vracet nějaký "bezpečný" pin?
	return START_BUTTON_PIN;
}

bool buttonActive(byte button, byte state)
{
	// TODO mapovat podle INPUT/INPUT_PULLUP?
	if (button <= ACTION_BUTTON)	// start and action buttons
		return state == HIGH;
	return state == LOW;			// joystick buttons
}

bool buttonDown(byte button)
{
	byte state = digitalRead(buttonPin(button));
	return buttonActive(button, state);
}

bool buttonPressed(byte button) 
{
	// holds last states of all buttons (currently 7 total)
	static byte lastButtonState = 0;
	
	byte state = digitalRead(buttonPin(button));
	bool active = buttonActive(button, state);
	if (active && state != bitRead(lastButtonState, button)) {
		bitWrite(lastButtonState, button, active);
		return true;
	}
	bitWrite(lastButtonState, button, active);
	return false;
}

void playTone(int pitch, int time)
{
	tone(BUZZER_PIN, pitch, time);
}

void softReset()
{
	asm volatile("jmp 0");
}
