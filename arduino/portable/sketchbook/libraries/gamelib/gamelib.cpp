#include "gamelib.h"

void initGame(byte initFlags)
{
	if (initFlags & BUTTONS) {
		pinMode(START_BUTTON_PIN, INPUT_PULLUP);
  		pinMode(ACTION_BUTTON_PIN, INPUT_PULLUP);
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
	Serial.begin(9600);
	randomSeed(analogRead(0));
}

// TODO better? redefine g++ -include? wrap g++ -wrap?
void softReset()
{
#ifdef NOT_ARDUINO
    exit(0);
#else
    asm volatile("jmp 0");
#endif
}
