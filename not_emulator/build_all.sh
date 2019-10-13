#!/bin/bash

# build all games
# all arguments are propagated to build.sh script
# stops immediately if one of the games fails to compile
# TODO currently does not stop on error...fix and add parameter to ignore errors and continue?
# TODO compile multiple games at a time

# TODO skip games that were not modified
#      binary modified time is newer than game files, gamelib files and not_emulator files

BIN="bin"

mkdir -p "$BIN"

for game in $(ls ../games); do
	echo "Building '$game'"
	echo "---------------------------------"
    ./build.sh "$@" "$game"
	rc=$?
	if [[ $rc != 0 ]]; then
		echo
		echo "Failed to build '$game'"
		exit 1
	fi
	echo
done

echo "All games built successfully"
