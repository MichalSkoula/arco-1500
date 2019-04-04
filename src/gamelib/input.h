#ifndef _GAMELIB_INPUT_H
#define _GAMELIB_INPUT_H

#include <Arduino.h>

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

// TODO add ANY_BUTTON? START_OR_ACTION_BUTTON?
enum Buttons {
	START_BUTTON 	= 0,
	ACTION_BUTTON	= 1,

	LEFT_BUTTON		= 2,
	UP_BUTTON		= 3,
	RIGHT_BUTTON	= 4,
	DOWN_BUTTON		= 5,
	CENTER_BUTTON	= 6
};

bool buttonDown(byte button);

// read and update button state
// return true when the button is pressed and then always false until
// the button is released and pressed again
// should not be called more than once per button per loop()
// for classical buttons loop() should have at least 3 ms of delay to filter out fake release
// TODO asi nefunguje pro joystick?
bool buttonPressed(byte button);

#endif	/* _GAMELIB_INPUT_H */
