#ifndef GAMELIB_INPUT_H
#define GAMELIB_INPUT_H

#include <Arduino.h>

enum Pins {
	START_BUTTON_PIN 	= 3,
	ACTION_BUTTON_PIN 	= 2,

	LEFT_BUTTON_PIN 	= 12,
	UP_BUTTON_PIN 		= 11,
	RIGHT_BUTTON_PIN 	= 10,
	DOWN_BUTTON_PIN 	= 8,
	CENTER_BUTTON_PIN 	= 9,

	BUZZER_PIN 			= 13
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

// read button state
bool buttonPressed(byte button);

// returns true when the button has been pressed for more than ms milliseconds
// then returns false until the button is released
// CAN ONLY BE CALLED FOR ONE BUTTON AT A TIME
// to reset call with 0 ms
bool buttonPressed(byte button, uint32_t ms);

#endif	/* GAMELIB_INPUT_H */
