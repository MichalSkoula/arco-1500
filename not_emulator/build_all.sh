#!/bin/bash

# build all games
# stops immediately if one of the games fails to compile
# binaries are copied to directory bin

# TODO skip games that were not modified
#      binary modified time is newer than game files, gamelib files and not_emulator files

BIN="bin"

mkdir -p "$BIN"

for game in $(ls ../games); do
	echo "Building '$game'"
	echo "---------------------------------"
	./build.sh "$game"
	rc=$?
	if [[ $rc != 0 ]]; then
		echo
		echo "Failed to build '$game'"
		exit 1
	fi
	mv "build/$game" "bin/$game"
	echo
done

echo "All games built successfully"
