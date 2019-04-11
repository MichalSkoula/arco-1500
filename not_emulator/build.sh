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
LIBS="../arduino/portable/sketchbook/libraries"
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
# TODO OR just write all forward declarations by hand for every game?

ARDUINO="../arduino"
if [ -f "$ARDUINO/arduino-builder" ]; then
    echo "Running arduino-builder (portable) in '$ARDUINO'"

    "$ARDUINO/arduino-builder"                      \
        -preprocess 								\
        -hardware "$ARDUINO/hardware"       		\
        -tools "$ARDUINO/tools-builder"     		\
        -tools "$ARDUINO/hardware/tools/avr"   		\
        -libraries "$LIBS"                  		\
        -fqbn=arduino:avr:nano:cpu=atmega328		\
        -build-path "$PREP"							\
        "$SKETCH"									> /dev/null
else
    ARDUINO="/usr/share/arduino"
    echo "Running arduino-builder (system) in '$ARDUINO'"

    # copy gamelib to default Arduino IDE Sketchbook location
    # TODO read location from ~/.arduino15/preferences.txt sketchbook.path=?
    mkdir -p "$HOME/Arduino/libraries/gamelib"
    cp "$LIBS/gamelib/"* "$HOME/Arduino/libraries/gamelib"

    "$ARDUINO/arduino-builder"                      \
        -preprocess 								\
        -hardware "$ARDUINO/hardware"       		\
        -tools "$ARDUINO/tools-builder"     		\
        -libraries "$HOME/Arduino/libraries"    	\
        -fqbn=arduino:avr:nano:cpu=atmega328		\
        -build-path "$PREP"							\
        "$SKETCH"									> /dev/null
fi

cp "$PREP/sketch/$1.ino.cpp" "$BUILD/main.cpp"
cat main.cpp >> "$BUILD/main.cpp"

# TODO cmake
# TODO -Wconversion
cd "$BUILD"
g++ -std=c++17                                                  \
    -Wall -Wpedantic -pedantic-errors -Wextra                   \
    -I ".." -I "../$LIBS/gamelib"                               \
    -D "WINDOW_TITLE=\"not_emulator - $1\""                     \
    -o "$1"                                                     \
    main.cpp ../Arduino.cpp ../EEPROM.cpp ../U8g2lib.cpp        \
    "../$LIBS/gamelib/"*.cpp                                    \
	-lSDL2 -lSDL2_ttf
