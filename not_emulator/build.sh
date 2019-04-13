#!/bin/bash

# ./build.sh <game directory name>
# e.g. ./build.sh galaxy_madness

# TODO add parameter --no-arduino to use fallback option instead of arduino-builder

if [ "$#" -ne 1 ]; then
	echo "Must be called with exactly one parameter - name of the game"
	echo "See the games directory"
	exit
fi

GAME="../games/$1"
BUILD="build"
MAIN="main.cpp"
LIBS="../arduino/portable/sketchbook/libraries"

SKETCH="$GAME/$1.ino"
if [ ! -f "$SKETCH" ]; then
	echo "Sketch with path '$SKETCH' does not exist"
	exit
fi

if [ -d "$BUILD" ]; then
	rm -r "$BUILD"
fi
mkdir "$BUILD"

ARDUINO_PORT="../arduino"
ARDUINO_SYS="/usr/share/arduino"
# TODO [ ! no-arduino ] && { ... }
if [ -f "$ARDUINO_PORT/arduino-builder" ] || [ -f "$ARDUINO_SYS/arduino-builder" ]; then
    PREP="$BUILD/preprocess"
    mkdir -p "$PREP"

    ARDUINO="$ARDUINO_PORT"
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
        ARDUINO="$ARDUINO_SYS"
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
else
    echo "Concatenating game .ino files (no arduino)..."
    # --------------------------------------------------
    # concatenate all .ino files into one file main.cpp
    # --------------------------------------------------
    echo -e "#include <Arduino.h>" > "$BUILD/$MAIN"

    # TODO probably lots of problems
    # TODO multiline /**/ comments can cause problems
    # TODO default values (meh, arduino can't deal with them either)

    # extract structs and classes from all .ino files and add as forward declarations
    grep -oE --no-filename '^(struct|class).*?\s*\{?\s*$' "$GAME/"*.ino     | \
        sed 's/{//g' | sed 's/$/;/g'                                        >> "$BUILD/$MAIN"

    # extract function headers from all .ino files and add as forward declarations
    #   match everything that resembles function header
    #   filter out lines starting if/else/for/...
    #   remove { and add semicolon ; at the end of every line
    grep -oE --no-filename '^([^/\*\}])*\(.*?\)\s*\{?\s*$' "$GAME/"*.ino    | \
        grep -E --invert-match '\s*(if|else|else if|switch|for|while|do)'   | \
        sed 's/{//g' | sed 's/$/;/g'                                        >> "$BUILD/$MAIN"

    cat "$SKETCH" >> "$BUILD/$MAIN"

    for file in "$GAME/"*.ino; do
        if [ "$file" != "$SKETCH" ]; then
            cat "$file" >> "$BUILD/$MAIN"
        fi
    done
fi

cat "$MAIN" >> "$BUILD/$MAIN"

# TODO cmake
# TODO -Wconversion
cd "$BUILD"
echo "Compiling..."
g++ -std=c++17                                                  \
    -Wall -Wpedantic -pedantic-errors -Wextra                   \
    -I ".." -I "../$LIBS/gamelib"                               \
    -D "WINDOW_TITLE=\"not_emulator - $1\""                     \
    -o "$1"                                                     \
    "$MAIN" ../Arduino.cpp ../EEPROM.cpp ../U8g2lib.cpp         \
    "../$LIBS/gamelib/"*.cpp                                    \
	-lSDL2 -lSDL2_ttf
