#ifndef _GAMELIB_H
#define _GAMELIB_H

#include "display.h"
#include "input.h"
#include "score.h"

// 128x64 pixels
constexpr byte DISPLAY_WIDTH = 128;
constexpr byte DISPLAY_HEIGHT = 64;

enum InitFlags {
	BUTTONS 	= 1,
	JOYSTICK 	= 2,
	SOUND 		= 4,
	INIT_ALL 	= 0xFF
};

// called in setup() with ORed mask of desired init flags
void initGame(byte initFlags);

// play tone for 10 ms by default
void playTone(int pitch, int time = 10);

// soft reset
void softReset();

#endif	/* _GAMELIB_H */
