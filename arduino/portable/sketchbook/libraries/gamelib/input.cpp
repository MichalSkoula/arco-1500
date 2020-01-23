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

constexpr uint32_t DEBOUNCE_THRESHOLD = 150;

// TODO optimize size
static uint32_t lastDebounceTime[7] = { 0, 0, 0, 0, 0, 0, 0 };
static uint32_t pressedTime = 0;

// TODO debounce only the change: not pressed -> pressed?
//      then return always true if pressed?
bool buttonPressed(byte button)
{
	// read the state of the switch into a local variable
	bool pressed = !digitalRead(buttonPin(button));

	// it delay is over, we can return the real state
    if (pressed && ((millis() - lastDebounceTime[button]) > DEBOUNCE_THRESHOLD)) {
		lastDebounceTime[button] = millis();
		return true;
	} 
	return false;
}

bool buttonPressed(byte button, uint32_t ms)
{
    // just reset state
    if (ms == 0) {
        pressedTime = 0;
        return false;
    }

    // debounce the initial press
    if (pressedTime == 0) {
        bool pressed = buttonPressed(button);
        if (pressed)
            pressedTime = millis() - DEBOUNCE_THRESHOLD;
        return false;
    }

    // button released - reset state
    if (digitalRead(buttonPin(button))) {
        pressedTime = 0;
        return false;
    }

    // return true if button has been pressed for more than ms milliseconds
    if ((millis() - pressedTime) > ms) {
        pressedTime = 0;
        return true;
    }
    return false;
}
