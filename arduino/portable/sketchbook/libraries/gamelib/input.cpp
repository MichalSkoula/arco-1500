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

	return START_BUTTON_PIN;
}

unsigned long lastDebounceTime[7] = {0, 0, 0, 0, 0, 0, 0};

bool buttonPressed(byte button)
{
	// read the state of the switch into a local variable
	bool pressed = !digitalRead(buttonPin(button));

	// it delay is over, we can return the real state
	if ((millis() - lastDebounceTime[button]) > 200 && pressed) {
		lastDebounceTime[button] = millis();
		return true;
	} 
	return false;
}
