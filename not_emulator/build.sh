#!/bin/bash

# ./build.sh [--no-arduino] [--size <size>] <game_name>
#
# --size <size>     original resolution 128x64 is multiplied by <size> (must be positive integer)
#
# e.g. ./build.sh galaxy_madness

NO_ARDUINO=0
RESOLUTION_MULTIPLIER=5
while [ "$#" -gt 1 ]; do
    if [ "$1" == "--no-arduino" ]; then
        NO_ARDUINO=1
        shift
    elif [ "$1" == "--size" ]; then
        RESOLUTION_MULTIPLIER="$2"
        shift
        shift
    fi
done

GAMES="../games"
if [ "$#" -ne 1 ]; then
    echo "Usage: build.sh [--no-arduino] [--size <size>] <game_name>"
    echo -e "\nAvailable games:"
    ls "$GAMES"
    echo
    exit 1
fi

GAME="$1"
GAMEDIR="$GAMES/$GAME"
BUILD="build/$GAME"
MAIN="main_$GAME.cpp"
LIBS="../arduino/portable/sketchbook/libraries"

SKETCH="$GAMEDIR/$GAME.ino"
if [ ! -f "$SKETCH" ]; then
	echo "Sketch with path '$SKETCH' does not exist"
    exit 1
fi

# TODO only when --rebuild param specified?
#if [ -d "$BUILD" ]; then
#	rm -r "$BUILD"
#fi
mkdir -p "$BUILD"

ARDUINO_PORT="../arduino"
ARDUINO_SYS="/usr/share/arduino"

if [ "$NO_ARDUINO" -eq 0 ] && \
 { [ -f "$ARDUINO_PORT/arduino-builder" ] || [ -f "$ARDUINO_SYS/arduino-builder" ]; } then
    PREP="$BUILD/preprocess"
    mkdir -p "$PREP"

    ARDUINO="$ARDUINO_PORT"
    if [ -f "$ARDUINO/arduino-builder" ]; then
        # absolute path
        cd "$(dirname "$ARDUINO")"
        ARDUINO="$(pwd)/$(basename "$ARDUINO")"
        cd "$OLDPWD"

        echo "Running arduino-builder (portable) in '$ARDUINO'"

        "$ARDUINO/arduino-builder"                      \
            -preprocess 								\
            -hardware "$ARDUINO/hardware"       		\
            -tools "$ARDUINO/tools-builder"     		\
            -tools "$ARDUINO/hardware/tools/avr"   		\
            -built-in-libraries "$ARDUINO/libraries"    \
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
        cp -u "$LIBS/gamelib/"* "$HOME/Arduino/libraries/gamelib"

        # TODO add some parameters from portable version
        "$ARDUINO/arduino-builder"                      \
            -preprocess 								\
            -hardware "$ARDUINO/hardware"       		\
            -tools "$ARDUINO/tools-builder"     		\
            -libraries "$HOME/Arduino/libraries"    	\
            -fqbn=arduino:avr:nano:cpu=atmega328		\
            -build-path "$PREP"							\
            "$SKETCH"									> /dev/null
    fi

    cp "$PREP/sketch/$GAME.ino.cpp" "$BUILD/$MAIN"
else
    echo "Concatenating game .ino files (no arduino)..."
    # --------------------------------------------------
    # concatenate all .ino files into one file main.cpp
    # --------------------------------------------------
    echo -e "#include <Arduino.h>" > "$BUILD/$MAIN"

    # TODO probably lots of problems
    # TODO multiline /**/ comments can cause problems
    # TODO default values (meh, arduino-builder can't deal with them either)
    # TODO make work with flappy_cat and space_surfer - classes

    # extract structs and classes from all .ino files and add as forward declarations
    grep -oE --no-filename '^(struct|class).*?\s*\{?\s*$' "$GAMEDIR/"*.ino      | \
        sed 's/{//g' | sed 's/$/;/g'                                            >> "$BUILD/$MAIN"

    # extract function headers from all .ino files and add as forward declarations
    #   match everything that resembles function header
    #   filter out lines starting if/else/for/...
    #   remove { and add semicolon ; at the end of every line
    grep -oE --no-filename '^([^/\*\}])*\(.*?\)\s*\{?\s*$' "$GAMEDIR/"*.ino     | \
        grep -E --invert-match '\s*(if|else|else if|switch|for|while|do)'       | \
        sed 's/{//g' | sed 's/$/;/g'                                            >> "$BUILD/$MAIN"

    cat "$SKETCH" >> "$BUILD/$MAIN"

    for file in "$GAMEDIR/"*.ino; do
        if [ "$file" != "$SKETCH" ]; then
            cat "$file" >> "$BUILD/$MAIN"
        fi
    done
fi

cat "main.cpp" >> "$BUILD/$MAIN"

# TODO better fonts?
# font path in Fedora
FONT="/usr/share/fonts/dejavu/DejaVuSansMono.ttf"
if [ ! -f "$FONT" ]; then
    # font path in Ubuntu
    FONT="/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"
    if [ ! -f "$FONT" ]; then
        echo "Cannot find DejaVuSansMono.ttf font"
        exit 1
    fi
fi

# TODO cmake
# TODO -Wconversion
cd "$BUILD"
echo "Compiling..."

# relative to $BUILD
REL="../.."

g++ -std=c++17                                                  \
    -Wall -Wpedantic -pedantic-errors -Wextra                   \
    -I "$REL" -I "$REL/$LIBS/gamelib"                           \
    -D "RESOLUTION_MULTIPLIER=$RESOLUTION_MULTIPLIER"           \
    -D "WINDOW_TITLE=\"not_emulator - $GAME\""                  \
    -D "FONT_BIG_PATH=\"$FONT\"" -D "FONT_SMALL_PATH=\"$FONT\"" \
    -o "$GAME"                                                  \
    "$MAIN" "$REL/"{Arduino,EEPROM,U8g2lib,utils}.cpp           \
    "$REL/$LIBS/gamelib/"{gamelib,display,input,sound}.cpp      \
	-lSDL2 -lSDL2_ttf -D SDL_MAIN_HANDLED

if [ ! -f "$GAME" ]; then
    echo "Failed to compile '$GAME'"
    exit 1
fi
mv "$GAME" "$REL/bin"

echo "Done."
