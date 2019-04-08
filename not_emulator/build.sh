#!/bin/bash

# ./build.sh <game directory name>
# e.g. ./build.sh galaxy_madness

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

# TODO cmake
# TODO -Wconversion
cd "$BUILD"
g++ -std=c++17                                                                  \
    -Wall -Wpedantic -pedantic-errors -Wextra                                   \
    -I ".." -I "../../arduino/portable/sketchbook/libraries/gamelib"            \
    -D "WINDOW_TITLE=\"not_emulator - $1\""                                     \
	-o "$1"																		\
    main.cpp ../Arduino.cpp ../EEPROM.cpp ../U8g2lib.cpp                    	\
    ../../arduino/portable/sketchbook/libraries/gamelib/*.cpp                   \
	-lSDL2 -lSDL2_ttf
