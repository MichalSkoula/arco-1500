#include "input.h"

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
    (void)button;
    return state == LOW;        // everything is now INPUT_PULLUP
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
