#!/bin/sh

printf "\ncreate release folder ..."
rm arco1500.zip
mkdir arco1500-release

printf "\ncopying arduino ide ..."
cp -R arduino arco1500-release/arduino
rm -Rf arco1500-release/arduino/portable/staging
rm -Rf arco1500-release/arduino/portable/*json*
rm -Rf arco1500-release/arduino/portable/preferences.txt

printf "\ncopying game uploader exe ..."
cp game_uploader/bin/Release/ARCO1500_Uploader.exe arco1500-release/ARCO1500_Uploader.exe

printf "\ncopying not_emulator ..."
cp -R not_emulator arco1500-release/not_emulator

printf "\ncopying games ..."
cp -R games arco1500-release/games

printf "\nzipping ..."
7z a -tzip arco1500.zip arco1500-release > 7zlog
rm -Rf arco1500-release
rm 7zlog
