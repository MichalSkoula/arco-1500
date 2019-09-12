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

// read and update button state
// return true when the button is pressed and then always false until
// the button is released and pressed again
// should not be called more than once per button per loop()
// for classical buttons loop() should have at least 3 ms of delay to filter out fake release
// TODO asi nefunguje pro joystick?
bool buttonPressed(byte button);

#endif	/* GAMELIB_INPUT_H */
