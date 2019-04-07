#!/bin/bash

# ./build <game directory name>
# e.g. ./build galaxy_madness

#/usr/share/arduino/arduino-builder -preprocess -logger=machine -hardware /usr/share/arduino/hardware -tools /usr/share/arduino/tools-builder -built-in-libraries /usr/share/arduino/libraries -libraries /home/david/Arduino/libraries -fqbn=arduino:avr:nano:cpu=atmega328 -ide-version=10805 -build-path /tmp/test_build -warnings=all -build-cache /tmp/test_cache -prefs=build.warn_data_percentage=75 -verbose /home/david/projects/arduino_handheld_game_console/src/games/galaxy_madness/galaxy_madness.ino

if [ "$#" -ne 1 ]; then
	echo "Must be called with exactly one parameter - name of the game"
	echo "See the games directory"
	exit
fi

SKETCH="../games/$1/$1.ino"
BUILD="build"
PREP="$BUILD/preprocess"

if [ ! -f "$SKETCH" ]; then
	echo "Sketch with path '$SKETCH' does not exist"
	exit
fi

if [ -d "$BUILD" ]; then
	rm -r "$BUILD"
fi
mkdir "$BUILD"
mkdir "$PREP"

# TODO get rid of arduino-builder dependency - concat .ino files and "just" add forward declarations
# TODO ctags? nope just replacing dependency with another one
/usr/share/arduino/arduino-builder				\
	-preprocess 								\
	-hardware /usr/share/arduino/hardware 		\
	-tools /usr/share/arduino/tools-builder		\
	-libraries ~/Arduino/libraries				\
	-fqbn=arduino:avr:nano:cpu=atmega328		\
	-build-path "$PREP"							\
	"$SKETCH"									> /dev/null

cp "$PREP/sketch/$1.ino.cpp" "$BUILD/main.cpp"
cat main.cpp >> "$BUILD/main.cpp"

# TODO cmake?
# TODO warnings
cd "$BUILD"
g++ -D "WINDOW_TITLE=\"not_emulator - $1\"" -I ".." -I "../../gamelib" 			\
	-o "$1"																		\
	main.cpp ../Arduino.cpp ../EEPROM.cpp ../U8g2lib.cpp ../../gamelib/*.cpp	\
	-lSDL2 -lSDL2_ttf
# -fmax-errors=5
# -std=c++14
